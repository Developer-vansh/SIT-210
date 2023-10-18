import { Temprature } from "../models/temp.js"
import { HeartRate} from "../models/bp.js"

export const saveTempData = async (data) => {
    data = new Temprature(data);
    data = await data.save();
    console.log('Saved data:', data);
  }
 export const saveHeartRateData = async (data) => {
    data = new HeartRate(data);
    data = await data.save();
    console.log('Saved data:', data);
  }