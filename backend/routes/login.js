
const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
// const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.cardnumber && request.body.password){
      const cardnumber = request.body.cardnumber;
      const password = request.body.password;
        
      card.checkPassword(cardnumber, function(dbError, dbResult) {
          if(dbError){
            if (dbError.errno = -4078){   // JOS DATABASE NURIN
              console.log("database offline");
              response.send(false);
            }
            else
            response.json(dbError.errno);
          }
          else
          {
            if (dbResult.length > 0) {
              bcrypt.compare(password,dbResult[0].password, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ cardno: cardnumber });
                  response.send(token);
                }
                else {
                    console.log("Wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("Card does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{

      console.log("Cardnumber or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(cardno) {
    dotenv.config();
    return jwt.sign(cardno, process.env.MY_TOKEN, { expiresIn: '1800s' });
  }
  

module.exports=router;

/*
const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const student = require('../models/student_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.id_student && request.body.password){
      const id_student = request.body.id_student;
      const password = request.body.password;
        student.checkPassword(id_student, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError.errno);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(password,dbResult[0].password, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ username: id_student });
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("id_student or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
    dotenv.config();
    return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
  }
  

module.exports=router;
*/