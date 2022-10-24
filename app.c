/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app.h"
#include "app_log.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"

#define SIGNAL_BTN_PRESS  1

#define CHAR_HANDLE       17
#define PAYLOAD_LENGTH    5
#define MAX_CONNECTIONS   2

#define CONN_INTERVAL     32 //40 msec


//1s is 32768 tick
#define TIMER_1S_PERIOD 32768

#define SCANNING_TIMEOUT 5*TIMER_1S_PERIOD

uint8_t payload[PAYLOAD_LENGTH] = {3};

uint16_t payload_sent_len;

typedef struct conn_data{
  uint8_t conn_handle;
  uint8_t char_handle;
}conn_data;


static uint8_t conn_handles[MAX_CONNECTIONS];
static uint8_t num_of_connections = 0;

static uint16_t v_major, v_minor, v_patch;

static uint64_t tick_start, tick_end;
static uint32_t latency_msec, elapsed_time;
static uint8_t received_cnt = 0;

static uint8_t connections_finished = 0;
static uint8_t Connection_Handle = 0;

/// Type of System State Machine
typedef enum {
  //Scanning for Connectable Beacons state
  INIT = 0,
  SCANNING_AND_CONNECTING,
  SCAN_STOP,
  WAITING_FOR_TEST_TO_START,
  //CONNECTING_TO_DEVICES,
  BEFORE_WRITTING,
  WRITTING,
  WAITING_FOR_RESPONSE,
  RESPONSE_RECEIVED,
  TEST_CONCLUDED

} SMType_t;

static SMType_t SM_status = 0;

typedef union{
        struct{
            uint8_t     byte_0;
            uint8_t     byte_1;
            uint8_t     byte_2;
            uint8_t     byte_3;
            }Bytes;
        uint32_t value;
    } _32_8bit;

volatile _32_8bit tick_count;

// Handle for sleeptimer
sl_sleeptimer_timer_handle_t my_sleeptimer_handle;



// Advertised service UUID
static const uint8_t advertised_service[2] = { 0xCC, 0xCC };


///**************************************************************************//**
// * Parse advertisements looking for  a header of the peripheral device
// * @param[in] data: Advertisement packet
// * @param[in] len:  Length of the advertisement packet
// * @param[in] ref_data: Reference advertisement header
// * @param[in] ref_len:  Length of the reference advertisement header
// *****************************************************************************/
//static uint8_t find_header_in_advertisement(uint8_t *data, uint8_t *ref_data, uint8_t ref_len)
//{
//  if (memcmp(*data, *ref_data, ref_len) == 0) {
//      app_log("Match \n\r");
//      return 1;
//
//        }
//
//  app_log("Not Match \n\r");
//  return 0;
//}

/**************************************************************************//**
 * Parse advertisements looking for  a service UUID of the peripheral device
 * @param[in] data: Advertisement packet
 * @param[in] len:  Length of the advertisement packet
 *****************************************************************************/
static uint8_t find_service_in_advertisement(uint8_t *data, uint8_t len)
{
  uint8_t ad_field_length;
  uint8_t ad_field_type;
  uint8_t i = 0;
  // Parse advertisement packet
  while (i < len) {
    ad_field_length = data[i];
    ad_field_type = data[i + 1];
    // Partial ($02) or complete ($03) list of 16-bit UUIDs
    if (ad_field_type == 0x02 || ad_field_type == 0x03) {
      // compare UUID to Health Thermometer service UUID
      if (memcmp(&data[i + 2], advertised_service, sizeof(advertised_service)) == 0) {
        return 1;
      }
    }
    // advance to the next AD struct
    i = i + ad_field_length + 1;
  }
  return 0;
}

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
  GPIO_PinModeSet(gpioPortD, 2,  gpioModeInput, 0);

  sl_sleeptimer_init();

}

/**************************************************************************//**
 * @brief
 *   Sleeptimer callback function. Each time sleeptimer reaches timeout value,
 *   this callback is executed.
 *****************************************************************************/
void sleeptimer_cb(sl_sleeptimer_timer_handle_t *handle, void *data)
{

  tick_count.value+=1;
  if(SM_status==SCANNING_AND_CONNECTING){
      SM_status = SCAN_STOP;
  }

}



/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  sl_status_t sc;

//  if(( GPIO_PinInGet(gpioPortD,2)==0)&&(num_of_connections >= MAX_CONNECTIONS))
//    {
//      sl_bt_external_signal(SIGNAL_BTN_PRESS);
//    }

  switch(SM_status)
  {

    case INIT:
      break;
      case SCANNING_AND_CONNECTING:{

        break;
      }
      case SCAN_STOP:{

          app_log("Scanning stopped - Scanning Period concluded\r\n");
          sc = sl_bt_scanner_stop();
          app_assert_status(sc);
          SM_status = WAITING_FOR_TEST_TO_START;


          break;
        }
      case WAITING_FOR_TEST_TO_START:{

          if(( GPIO_PinInGet(gpioPortD,2)==0))//&&(connections_finished == 1))
            {
              app_log("Button pressed, starting the test\r\n");

              Connection_Handle = 0;
              SM_status = BEFORE_WRITTING;
           }
        }

        break;
      case BEFORE_WRITTING:
        {
          Connection_Handle = 0;
          SM_status = WRITTING;
        }
              break;


      case WRITTING:
        {
            tick_start = sl_sleeptimer_get_tick_count64();
            received_cnt = 0;

            if ((conn_handles[Connection_Handle] != 0xFF)&&(Connection_Handle<num_of_connections))
              {
                  app_log("Sending data to connection: %d\r\n", conn_handles[Connection_Handle]);
                  sc = sl_bt_gatt_write_characteristic_value_without_response(conn_handles[Connection_Handle], CHAR_HANDLE, PAYLOAD_LENGTH, payload, payload_sent_len);
                  app_assert_status(sc);
                  SM_status =  WAITING_FOR_RESPONSE;
               }
            else Connection_Handle+=1;



//            for (uint8_t i = 0; i < MAX_CONNECTIONS; i++){
//                if (conn_handles[i] != 0xFF){
//                    app_log("Sending data to connection: %d\r\n", conn_handles[i]);
//                    sc = sl_bt_gatt_write_characteristic_value_without_response(conn_handles[i], CHAR_HANDLE, PAYLOAD_LENGTH, payload, payload_sent_len);
//                    app_assert_status(sc);
//                }
//            }
        }

        break;
      case WAITING_FOR_RESPONSE:
              {
                //Do Nothing
              }
              break;

      case RESPONSE_RECEIVED:
        {
          if(Connection_Handle<num_of_connections)
            {
              //Increases the Handle and start the Writting process to another device
              Connection_Handle+=1;
              SM_status = WRITTING;
            }
          //Max number of devices have been achieved, restarting the test with the first connected device
          else
            {
              SM_status = BEFORE_WRITTING;
            }
        }
        break;
      case TEST_CONCLUDED:
        {

        }
        break;

  }



}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      for (uint8_t i = 0; i < MAX_CONNECTIONS; i++){
          conn_handles[i] = 0xFF;
      }

      sl_bt_system_get_version(&v_major, &v_minor, &v_patch, NULL, NULL, NULL);
      app_log("Stack version: %d.%d.%d\r\n", v_major, v_minor, v_patch);

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);
      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];
      app_log("BLE address: %02x:%02x:%02x:%02x:%02x:%02x\r\n", address.addr[5],
              address.addr[4], address.addr[3], address.addr[2],
                address.addr[1], address.addr[0]);


      sc = sl_bt_connection_set_default_parameters(CONN_INTERVAL, CONN_INTERVAL, 0, CONN_INTERVAL * 5, 0, 0xFFFF);
      app_assert_status(sc);
      app_log("Connection interval set to 40 msec\r\n");

      sc = sl_bt_scanner_start(sl_bt_scanner_scan_phy_1m,
                               sl_bt_scanner_discover_generic);
      app_assert_status(sc);
      app_log("Scanning started\r\n");


      //Initiates Scanner Counter timer
      sc = sl_sleeptimer_start_timer(&my_sleeptimer_handle,  SCANNING_TIMEOUT, sleeptimer_cb, (void *)NULL,0,0);
      app_assert_status(sc);


      SM_status = SCANNING_AND_CONNECTING;



      break;

    case sl_bt_evt_scanner_legacy_advertisement_report_id:

      if(find_service_in_advertisement(evt->data.evt_scanner_legacy_advertisement_report.data.data, evt->data.evt_scanner_legacy_advertisement_report.data.len)){

          app_log("Device found\r\n");
          sc = sl_bt_connection_open(evt->data.evt_scanner_legacy_advertisement_report.address,
                                sl_bt_gap_public_address,
                                sl_bt_gap_phy_1m,
                                &conn_handles[num_of_connections]);
          app_assert_status(sc);
      }
      break;

    case sl_bt_evt_scanner_scan_report_id:
      app_log("Scan report\r\n");
      break;


    case sl_bt_evt_connection_parameters_id:
      //app_log("connection interval: %d\r\n", evt->data.evt_connection_parameters.interval);
      break;
    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:

      num_of_connections++;
      app_log("Connection opened, number of connections: %d\r\n", num_of_connections);
      if (num_of_connections >= MAX_CONNECTIONS){

          app_log("Max number of connections achieved -  %d Connections \r\n", num_of_connections);
          connections_finished = 1;

      }

      break;


    case sl_bt_evt_gatt_server_attribute_value_id:
      {
        app_log("Response received\r\n");
        received_cnt++;
        tick_end = sl_sleeptimer_get_tick_count64();
        elapsed_time = tick_end - tick_start;
        //app_log("Elapsed time in ticks: %d\r\n", elapsed_time);
        latency_msec = sl_sleeptimer_tick_to_ms(elapsed_time);
        app_log("\n\rLatency: %d msec\r\n", latency_msec);
//        for(uint8_t i=0;i<64;i++)
//          {
//            app_log("%02X", evt->data.evt_gatt_server_attribute_value.value.data[i]);
//          }
//        app_log("/n/r");

        SM_status = RESPONSE_RECEIVED;







//      if (received_cnt == MAX_CONNECTIONS){
//          tick_end = sl_sleeptimer_get_tick_count64();
//          //app_log("End tick: %d\r\n", tick_end);
//          elapsed_time = tick_end - tick_start;
//          //app_log("Elapsed time in ticks: %d\r\n", elapsed_time);
//          latency_msec = sl_sleeptimer_tick_to_ms(elapsed_time);
//
//          for(uint8_t i=0;i<64;i++)
//            {
//              app_log("%02X", evt->data.evt_gatt_server_attribute_value.value.data[i]);
//            }
//
//          app_log("\n\rLatency: %d msec\r\n", latency_msec);
//
//      }

      }
      break;

    case sl_bt_evt_system_external_signal_id:
       if(evt->data.evt_system_external_signal.extsignals == SIGNAL_BTN_PRESS){}

         break;
    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      app_log("connection closed\r\n");
      for (uint8_t i = 0; i < MAX_CONNECTIONS; i++){
               if (conn_handles[i] == evt->data.evt_connection_closed.connection){
                   conn_handles[i] = 0xFF;
                   break;
               }
           }
      num_of_connections--;
      if (num_of_connections < MAX_CONNECTIONS){
            sc = sl_bt_scanner_start(sl_bt_scanner_scan_phy_1m,
                                     sl_bt_scanner_discover_generic);
            if (sc == 0x0002){
                app_log("Scan is already running\r\n");
            }
       }

      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

void sl_button_on_change(const sl_button_t *handle)
{
  sl_button_state_t state;
  if(handle->context == sl_button_btn0.context){
      state = sl_button_get_state(&sl_button_btn0);
      if(state == SL_SIMPLE_BUTTON_PRESSED){
          sl_bt_external_signal(SIGNAL_BTN_PRESS);
      }
  }
}
