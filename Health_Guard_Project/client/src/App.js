import './App.css'
import MainDash from './components/MainDash/MainDash';
import Sidebar from './components/Sidebar';
import React, { useEffect, useState } from 'react';
import DataState from './context/data/DataState';


function App() {

  return (
    <div className="App">
    <DataState>
      <div className="AppGlass">
        <Sidebar/>
        <MainDash/>
      </div>
    </DataState>
      
    </div>
  );
}

export default App;
