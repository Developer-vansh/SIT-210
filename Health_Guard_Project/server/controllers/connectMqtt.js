import { connect } from "mqtt"; // import connect from mqtt
export let client = connect('mqtt://broker.hivemq.com:1883'); // created a client
export const heartRate_mqtt_receive = 'Vansh_Iot/heartRate';
export const temprature_mqtt_receive = 'Vansh_Iot/temp';
export const emergency_mqtt_receive = 'emergency';
client.on('connect', async () => {
  console.log('MQTT Connected');
  await client.subscribe(heartRate_mqtt_receive);
  await client.subscribe(temprature_mqtt_receive);
  await client.subscribe(emergency_mqtt_receive);
})