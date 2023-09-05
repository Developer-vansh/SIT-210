import mongoose from "mongoose" ;
export const connectDB=()=>{
    mongoose
.connect("mongodb://127.0.0.1:27017",{
    dbName:"backendapi",
})
.then(()=>console.log("Db connected"))
.catch((e)=>console.log(e));
}