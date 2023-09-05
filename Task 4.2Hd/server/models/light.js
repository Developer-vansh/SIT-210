import mongoose from "mongoose";

const schema=new mongoose.Schema({
  red:Boolean,
  green:Boolean,
  blue:Boolean

});

export const LIGHT=mongoose.model("LIGHT",schema);