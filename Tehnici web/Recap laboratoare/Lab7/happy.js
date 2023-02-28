window.onload = function(){
  document.body.addEventListener('keydown', function(){
    for (let i = 0; i < 20; i++){
      var img = document.createElement("img");
      img.src = "sad.png";
      document.getElementById("container").appendChild(img);
    }
    document.querySelector("#game > p").style.visibility = "visible";
    var imagini = document.getElementsByTagName("img");
    for(let i = 0; i < imagini.length; i++){
      imagini[i].addEventListener("click", incScor);
    }
    var endJoc = setTimeout(gameover, 20000);
    endJoc;
  });
}

function gameover(){
  document.getElementsByTagName("h1")[0].innerHTML = "Jocul s-a terminat!";
  document.getElementById("container").remove();
}

function incScor(){
  var scor = Number(document.getElementById("scor").innerHTML);
  scor+=1;
  document.getElementById("scor").innerHTML = scor;
  this.src = "happy.png";
  this.removeEventListener('click', incScor);
}
