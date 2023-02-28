var express = require("express");
var app = express();
var vocale = ["A", "E", "I", "O", "U"];

app.listen('8080');

app.get('/proceseaza', function(req, res){
  var partiUrl = new URL(req.url, "http://localhost:8080/");
  var query = partiUrl.searchParams;
  var valid = true;
  var text1 = query.get('text1');
  var text2 = query.get('text2');
  if (text1 !== text1.toUpperCase())
    valid = false;
  var numere = text2.split(',');
  if (Number.isInteger(Number(numere[0])) && Number.isInteger(Number(numere[1]))){
    if (Number(numere[0]) < Number(numere[1]) && Number(numere[1]) < text1.length && Number(numere[0]) >= 0 && Number(numere[1]) >= 0);
    else{
      console.log(Number(numere[0]));
      console.log(Number(numere[1]));
      valid = false;
    }


  }
  else{
    console.log(Number(numere[0]));
    console.log(Number(numere[1]));
    valid = false;
  }

  if (valid === true){
    var nr1 = Number(numere[0]);
    var nr2 = Number(numere[1]);
    var vocRez = new Array;
    for (let i = nr1; i <= nr2; i++){
      if (vocale.includes(text1[i]))
        vocRez.push(text1[i]);
    }
    vocRez = vocRez.join(',');
    res.send(vocRez);
  }
  else
    res.send("Date invalide");
});
