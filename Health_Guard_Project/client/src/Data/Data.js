// Sidebar imports
import {
  UilEstate,
  UilClipboardAlt,
  UilUsersAlt,
  UilPackage,
  UilChart,
  UilSignOutAlt,
} from "@iconscout/react-unicons";

// Analytics Cards imports
import { UilUsdSquare, UilMoneyWithdrawal } from "@iconscout/react-unicons";
import { keyboard } from "@testing-library/user-event/dist/keyboard";
import { useContext } from 'use-context-selector';
import dataContext from "../context/data/dataContext";

// Recent Card Imports
import img1 from "../imgs/img1.png";
import img2 from "../imgs/img2.png";
import img3 from "../imgs/img3.png";

// Analytics Cards Data
export const cardsData = [
  {
    title: "Heart Rate",
    color: {
      backGround: "linear-gradient(180deg, #bb67ff 0%, #c484f3 100%)",
      boxShadow: "0px 10px 20px 0px #e0c6f5",
    },
    barValue: 70,
    value: "25,970",
    png: UilUsdSquare,
    series: [
      {
        name: "Heart Rate data",
        data: [40, 40, 40, 40, 40, 109, 40],
      },
    ],
  },
  {
    title: "Temprature",
    color: {
      backGround: "linear-gradient(180deg, #FF919D 0%, #FC929D 100%)",
      boxShadow: "0px 10px 20px 0px #FDC0C7",
    },
    barValue: 20,
    value: "14,270",
    png: UilMoneyWithdrawal,
    series: [
      {
        name: "Temprature data",
        data: [10, 100, 50, 70, 80, 30, 40],
      },
    ],
  },
 
];
