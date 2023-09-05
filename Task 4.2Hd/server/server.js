import express from "express"
import bodyParser from 'body-parser';
import path from 'path';
const app = express();
import { connectDB } from "./data/database.js";
connectDB();
import { LIGHT } from "./models/light.js";
const port = 3000;
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
//middlewares
app.use(express.json())
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

//routes
// app.get('/send', (req, res) => {
//   res.send(' Hello Vansh');
// });

app.get("/",(req,res)=>{
    
  res.sendFile(path.resolve()+"/index.html");

})
app.post('/updateLight', async (req, res) => {
  let { red, green, blue } = req.body;
  red= red=='on'?1:0
  green= green=='on'?1:0
   blue=blue=='on'?1:0
   console.log(red,green,blue);
  try {
    // Update the document with ObjectId '64f5c77823216652f8ab4786' in the LIGHTS collection
    const updatedLight = await LIGHT.findOneAndUpdate(
      { _id: '64f5c77823216652f8ab4786' },
      { $set: { red, green, blue } },
      { new: true }
    );

    if (updatedLight) {
      // res.json({
      //   success: true,
      //   message: 'Updated Successfully',
      //   updatedLight,
      // });
    } else {
      res.status(404).json({ success: false, message: 'Light not found' });
    }
  } catch (error) {
    console.error('Error updating light:', error);
    res.status(500).json({ error: 'Internal Server Error' });
  }
});

app.post('/createLight',async(req, res) =>{
  const{red,green,blue}=req.body;
  const light= await LIGHT.create({
 red,
 green,
 blue
  })
  res.json({
        success:true,
        message:"Updated Successfully"
    })
}
)
app.get('/send', async (req, res) => {
  try {
    // Assuming you want to retrieve all data from the LIGHT collection
    const lights = await LIGHT.findById("64f5c77823216652f8ab4786");
    
    // Prepare the data to send to the Arduino
    const responseData = {
      lights: lights, // Sending all light data
    };

    // Send the data as a JSON response
    res.json(responseData);
  } catch (error) {
    console.error('Error sending data:', error);
    res.status(500).json({ error: 'Internal Server Error' });
  }
});

