const mongoose = require('mongoose');
const bcrypt = require('bcrypt'); 
var mongoDB = 'mongodb://127.0.0.1/Users';
const SALT_ROUNDS = 10; 

mongoose.connect(mongoDB,{ useNewUrlParser: true } ,(err)=>{
    if (err){
        console.log("connection to db failed"); 
    }
    console.log("connection to db estblished");

});


var userSchema = new mongoose.Schema({
    username:{
        type : String, 
        unique : true,
        required : true, 
        trim : true 
    }, 
    email:{
        type : String,
        unique : true, 
        required : true, 
        trim : true 
    },
    password:{
        type : String, 
        required : true, 
        trim : true
    }
}); 

var user = mongoose.model('User', userSchema);

/*
* creates and add new user to db, return error if fails
*/
const registerUser = newUser => new Promise((resolve, reject) => {
    if(user.exists({username:newUser.username})
    .then(res => {
        if(res){
            console.log('user exists'); 
            resolve(false); 
        }
        else{
            bcrypt.hash(newUser.password, SALT_ROUNDS)
            .then(data => {
                console.log(data); 
                newUser.password = data; 
                user.create(newUser);
                console.log('user created');
                resolve(false) 
            }); 
        }
    }));
});

const findUser = newUser => new Promise((resolve, reject)=>{
    user.findOne({username:newUser.username})
    .then(newUser => {
        resolve(newUser);  
    })
    .catch(err =>{
        console.log(newUser.username + 'could not be found'); 
        reject(err);
    }); 
});

const deleteUser = userToDelete => new Promise((resolve, reject) =>{
    user.find({username:userToDelete.username})
    .then(res => {
        bcrypt.compare(userToDelete.password, res.password)
        .then(res => {
            if (res){
                user.deleteOne(res).then(err => {
                console.log('user deleted');
                resolve(res);
                });
            }
            else {
                console.log('invalid password'); 
                resolve(res); 
            }
        });   
    });
});  

/*registerUser({username:'Sunny', email:'Sunny@mailme.com', password:'12345678'});
registerUser({username:'Sunny', email:'Sunny@mailme.com', password:'12345678'});*/
//registerUser({username:'Loli', email:'loliland@mailme.com', password:'loli'});

//findUser({username:'Hooper'});
//findUser({username:'Sunny'});
//deleteUser({username:'Sunny'}); 
/*var found = findUser({username:'Sunny'}).then(res=>{
    console.log(res.email); 
});*/

//deleteUser({username:'Loli', password:'loli'}); 


registerUser({username:'Porke', email:'Porke@mailme.com', password:'12345678'});
registerUser({username:'PorkeSinur', email:'Porke@mailme.com', password:'12345678'});
registerUser({username:'koi', email:'koi@mailme.com', password:'koimeatlarge'});
deleteUser({username:'PorkeSinur',password:'123458'}).then(res =>{
    console.log('made it');
});



