var tasta;

window.onload = function(){
  for (let i = 0; i < 10; i++){
    var btn = document.createElement("button");
    btn.innerHTML = i;
    btn.classList.add("copil", "cifra" + i);
    document.body.appendChild(btn);
  }
  var butoane = document.getElementsByTagName("button");
  document.body.addEventListener("keydown", function(event){
    tasta = Number(event.key);
    butoane[tasta].classList.remove("cifra" +tasta);
    butoane[tasta].classList.add("black");
  });
  document.body.addEventListener("keyup", function(event){
    butoane[tasta].classList.remove('black');
    butoane[tasta].classList.add('cifra' + tasta);
  });
  /*for (let i = 0; i < butoane.length; i++){
    butoane[i].addEventListener()
  }*/

}
