import mongoose from "mongoose";
import moment from 'moment';
const schema=new mongoose.Schema({
    type: {
        type: String,
        required: true
    },
    value: {
        type: Number,
        required: true
    },
    createdAt: {
        type: Date,
        default: moment().utc().add(5, 'hours')
    }

});

export const Temprature=mongoose.model("Temp",schema);