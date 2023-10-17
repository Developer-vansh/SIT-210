
import { heart, temprature,emergency } from './mqtt.js';
import { wss } from '../app.js';


export const SendData=()=>{
   wss.on('connection', (ws) => {
     console.log('WebSocket connection established');
   
     // Simulate sending  updates at regular intervals
     const interval = setInterval(() => {
       ws.send(JSON.stringify({ heart,temprature,emergency }));
     }, 4000); // Send updates every second
   
     ws.on('close', () => {
       console.log('WebSocket connection closed');
       clearInterval(interval);
     });
   });
   
}

