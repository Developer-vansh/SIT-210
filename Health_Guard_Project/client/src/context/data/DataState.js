import DataContext from './dataContext';
import React, { useEffect, useState } from 'react';

const DataState=(props)=>{
    const [HeartRate, setHeartRate] = useState(0);
    const [Temprature, setTemprature] = useState(0);
    const [Emergency, setEmergency] = useState('false');
    const [heartGraph,setheartGraph]=useState({
        value:[],
        time:[]
      })
    const [tempratureGraph,settempratureGraph]=useState({
        value:[],
        time:[]
      })
    useEffect(() => {
      const socket = new WebSocket('ws://localhost:4001');
  
      socket.addEventListener('message', (event) => {
        const data = JSON.parse(event.data);
        setEmergency(data.emergency);      
        // console.log('emergency',data.emergency);
        setHeartRate(data.heart);
        var currentdate = new Date();
        var datetime =  currentdate.getFullYear() + '-' +
        (currentdate.getMonth() + 1) + '-' + // Month is zero-based, so add 1
        currentdate.getDate() + 'T' +
        currentdate.getHours() + ':' +
        currentdate.getMinutes() + ':' +
        currentdate.getSeconds() + '.000Z';
        // console.log(datetime)
        //updating the graph data for heart
        heartGraph.value.push(data.heart)
         heartGraph.time.push(datetime)    
         console.log( currentdate)
          //updating the graph data for pulse
        setTemprature(data.temprature);
        tempratureGraph.value.push(data.temprature)
        tempratureGraph.time.push(datetime) 
        console.log(heartGraph.time)
      });
  
      return () => {
        socket.close();
      };
    }, []);
    const data={
        'heartRate':HeartRate,
        'temprature':Temprature,
        'emergency':Emergency,
        'heartGraph':heartGraph,
        'tempratureGraph':tempratureGraph
    }
return (
    <DataContext.Provider value={data}>
        {props.children}
    </DataContext.Provider>
)
}

export default DataState;