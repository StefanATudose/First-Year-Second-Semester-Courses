var express = require("express");
const session = require("express-session");
var fs = require("fs");
var app = express();

app.use(express.static("views"));
app.use(express.static("session"));
app.use(express.urlencoded({extended: true}));
app.use("/postComm", express.json())
app.use(session({
  secret: 'sdlknsfsladfn',
  resave: true,
  saveUninitialized: false
}));
app.set('view engine', 'ejs');


function verif(user, parola){
  var useri = fs.readFileSync("useri.json");
  var ob = JSON.parse(useri);
  var lung = ob[0].length;
  for (let i = 0; i < lung; i++){
    if (user == ob[0][i] && parola == ob[1][i])
      return true;
  }
  return false;
}


app.post("/login", function(req, res){
  if (verif(req.body.username, req.body.password)){
    req.session.username = req.body.username;
    res.redirect("/index2.html");
  }
  else
    res.send("<html><body><h1>Date invalide!<h1><button><a href = 'http://localhost:8080'>Incearca din nou!</a></button></body><html>");
})

app.get("/logout", function(req, res){
  res.render('../session/logout', {'nume': req.session.username});
});

app.get("/destroySession", function(req, res){
  req.session.destroy();
  res.redirect("/index.html");
});

app.post("/postComm", function(req, res){
  res.send(req.body.nume + " (" + req.body.email + ")<br>" + req.body.comment + "<br><br>");
});

app.listen("8080", function(){
  console.log("Ascult la 8080");
});

app.use(function(req, res){
  res.status(404).send("<html><body><h1>ERROR 404 hehe</h1><h2>Page not found!</h2></body></html>");
});
