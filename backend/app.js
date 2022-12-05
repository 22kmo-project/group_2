var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var loginRouter = require('./routes/login');
var ownerRouter = require('./routes/owner');
var cardRouter = require('./routes/card');
var accountRouter = require('./routes/account');
var logsRouter = require('./routes/logs');

var app = express();


app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// SUOJAAMATON OSUUS
app.use('/login', loginRouter);
//app.use(authenticateToken);

//############SUOJATTU OSUUS##############
app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/owner', ownerRouter);   // polku
app.use('/card', cardRouter);   //    ("/polku)
app.use('/account', accountRouter);
app.use('/logs', logsRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

module.exports = app;
