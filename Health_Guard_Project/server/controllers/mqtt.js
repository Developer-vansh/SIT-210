import moment from 'moment';
import { client, emergency_mqtt_receive, heartRate_mqtt_receive, temprature_mqtt_receive } from './connectMqtt.js';
import {  saveHeartRateData, saveTempData} from "./saveData.js";
export let heart=0;
export let temprature=0;
export let emergency=0;

export const GetData=async ()=>{
client.on('message', async (topic, message) => {
  console.log('\n[MQTT Received] Topic:', topic, ', Message:', message.toString());

  let data = message.toString();
  data = JSON.parse(data);
   data.createdAt = moment().utc().add(5, 'hours');
  //saving in variable
  if (topic === heartRate_mqtt_receive) {
      heart = data.value;
      console.log(`Received heartRate: ${heart }`);
       // Save live data into database
       await saveHeartRateData(data);
    } 
   else  if (topic === temprature_mqtt_receive){
      temprature = data.value;
      console.log(`Received temprarture: ${temprature}`);
       // Save live data into database
      await saveTempData(data);
    } 
    if(topic === emergency_mqtt_receive){
        emergency=data.value;
        console.log(`Emergency: ${emergency}`);
    }
    //{"type":"emergeny","is":"true"}

})
}
