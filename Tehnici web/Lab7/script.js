function articole_noi()
{
  var articol = document.createElement("article");
  document.querySelector("#postari").appendChild(articol);
  var titlu = document.createElement("h3");
  titlu.innerHTML = document.getElementById("titlu").value;
  articol.appendChild(titlu);
}

document.querySelector("button").addEventListener("click", articole_noi);
