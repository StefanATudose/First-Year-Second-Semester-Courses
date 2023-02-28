window.onload = function()
{

}
function f()
{
    alert("MESAJ");

}



function ex2()
{
    var nume = prompt("Introduceti numele:");
    document.getElementById("salut").innerHTML="Bine ati venit " + nume.toUpperCase() + "!";
}

function ex3()
{
    const citate = ["Citat 1","Citat 2","Citat 3","Citat 4","Citat 5"];
    const random = Math.floor(Math.random() * citate.length);
    document.getElementById("exercitiu3").innerHTML=citate[random];
}

function ex4()
{   alerta="";
    var numar = prompt("Dati un numar intreg:");
    const carti=[{titlu:"Matilda", pagini:256},{titlu:"Little Women", pagini:569},{titlu:"Hobbit",pagini:300},{titlu:"Mandrie si prejudecata",pagini:450},{titlu:"Muntele vrajit",pagini:150}];
    for(let i=0;i<carti.length;i++)
        if(numar<carti[i].pagini)
            alerta+=carti[i].titlu + ", ";
    alert(alerta);
}

function lab61()
{
    var imagine = document.querySelectorAll("#galerie img");
    for(var ob of imagine)
    {   ob.src="https://cdn4.libris.ro/img/pozeprod/59/1002/D5/25875927.jpg";
        ob.alt="carte interesanta";
        ob.style.border = "10px solid blue";
    }
}

function lab62()
{   var colectia = document.querySelectorAll("figcaption");
    for(i=0;i<colectia.length;i++)
        colectia[i].innerHTML = "Figura " +(i+1);
}

function adauga(info)
{var articole = document.querySelectorAll("article");
for (let i = 0; i< articole.length; i++)
{
var par = document.createElement("p");
par.innerHTML = info;
articole[i].appendChild(par);
par.className = "stil";
}
}

function litere_mari()
{
  var paragrafe = document.querySelectorAll("p");
  for (var p of paragrafe)
    p.innerHTML = p.innerHTML.toUpperCase();
}

function articole_noi()
{
  var articol = document.createElement("article");
  document.querySelector("#postari").appendChild(articol);
  var titlu = document.createElement("h3");
  titlu.innerHTML = document.getElementById("titlu").value;
  articol.appendChild(titlu);
}

articole_noi();
