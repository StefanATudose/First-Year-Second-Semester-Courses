var express = require('express');
var fs=require("fs");
var app=express();

app.use(express.static("html"));

app.get(["/abc","/xyz"],function(req,res){
     console.log("Am primit o cerere");
     const mesaje=["Mesaj1","Mesaj2","Mesaj3","Mesaj4","Mesaj5"];
     var indice=Math.floor(Math.random()*mesaje.length);
     res.send(mesaje[indice]);
     });


app.get("/get1",function(req,res){

  console.log(req.query);
  var nota1=req.query.nota1;
  var nota2=req.query.nota2;
  var media=(parseInt(nota1)+parseInt(nota2))/2;
  var nume=req.query.nume;
  res.send("<h2>Studentul " + nume + " are media " + media + "</h2>");

});

app.use(express.urlencoded({extended:true}));

app.post("/get1",function(req,res){

  console.log(req.body);
  var nota1=req.body.nota1;
  var nota2=req.body.nota2;
  var media=(parseInt(nota1)+parseInt(nota2))/2;
  var nume=req.body.nume;
  res.send("<h2>Studentul " + nume + " are media " + media + "</h2>");

});

app.post("/post2",function(req,res){
 console.log(req.body);
 var cuv=req.body.cuvant;
 var lb=req.body.limba;
 const dictionar = [{cuvant:"carte", engleza:"book", franceza:"livre"}, {cuvant:"floare", engleza:"flower", franceza:"fleur"},{cuvant:"tablou", engleza:"picture", franceza:"photo"}, {cuvant:"film", engleza:"movie", franceza:"film"}];
 var traducere="Nu exista cuvantul"; 
 for(c of dictionar)
  if(cuv == c.cuvant)
  {
   if(lb=="engleza") traducere=c.engleza;
   else traducere=c.franceza;
  } 
  res.send(cuv+ " : " + traducere); 

});


app.post("/post3",function(req,res){
  console.log(req.body);
  var tip=req.body.tip;
  var cuvant=req.body.cuvant;
  fs.readFile("persoane.json", function(err,date){
   if(err) throw err;
   var persoane=JSON.parse(date);
   res.write("<html><body><ol>");
   for(p of persoane)     
    if(p[tip]==cuvant) res.write("<li>" + p.nume + " " + p.prenume + "</li>");
    
   res.write("</ol></body></html>");
   res.end();
    
   });
   });
   

app.listen(4000,function(){console.log("A pornit serverul");});
