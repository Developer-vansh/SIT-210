import React from "react";
import { useContext } from 'use-context-selector';
import dataContext from "../../context/data/dataContext";
import Cards from "../Cards/Cards";
import "./MainDash.css";
const MainDash = () => {
  const data=useContext(dataContext)
  console.log(data.emergency)
  return (
    <div className="MainDash">
      <div className="hh"><h1>Real Time Updates</h1></div>
      {data.emergency==='true'?<h1>Emergency on Bed1</h1>:""}
      {data.temprature>=104?<h1>Critical Situation On Bed1</h1>:""}
      <Cards />
    </div>
  );
};

export default MainDash;
