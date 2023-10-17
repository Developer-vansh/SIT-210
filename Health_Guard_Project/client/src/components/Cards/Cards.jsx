import React from "react";
import "./Cards.css";
import { cardsData } from "../../Data/Data";
import { useContext } from 'use-context-selector';
import dataContext from "../../context/data/dataContext";
import Card from "../Card/Card";

const Cards = () => {
  const data=useContext(dataContext)
  return (
    <div className="Cards">
      {cardsData.map((card, id) => {
        return (
          <div className="parentContainer" key={id}>
            <Card
              title={card.title}
              color={card.color}
              barValue={card.barValue}
              value={id==0?data.heartRate:data.temprature}
              png={card.png}
              series={card.series}
              graph={id==0?data.heartGraph:data.tempratureGraph}
            />
          </div>
        );
      })}
    </div>
  );
};

export default Cards;
