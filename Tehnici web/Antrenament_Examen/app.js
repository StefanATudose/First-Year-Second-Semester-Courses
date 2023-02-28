var express = require('express');
var app = express();
var persoane=[{nume:"Ion", sex:"m", varsta:3},{nume:"Oana", sex:"f", varsta:23},{nume:"Daria",sex:"f", varsta:10}, {nume:"Mihai", sex:"m", varsta:19}, {nume:"Gabriel", sex:"m", varsta:22}, {nume:"Simona", sex:"f", varsta:11}, {nume:"Bogdan", sex:"m", varsta:28}]


app.listen(8080);

app.get("/path", function(req, res){
  var url_parts = new URL(req.url, 'http://localhost:8080/');
  if (url_parts.pathname == '/path'){
    var query = url_parts.searchParams;
    var nume = query.get('Nume');
    var gasit = false;
    var minor, sex;
    for (let i = 0; i < persoane.length; i++){
      if (persoane[i].nume == nume){
        gasit = true;
        if (persoane[i].varsta < 18)
          minor = ", este minor";
        else
          minor = ", nu este minor";
        if (persoane[i].sex == 'm')
          sex = "baiat";
        else
          sex = "fata";
        break;
      }
    }
    if (gasit == true){
      res.send("<html><body><p>" + sex + minor + "</p></body><html>");
    }
    else
      res.send("<html><body><p>Nu exista numele cautat</p></body><html>");
    }
});
