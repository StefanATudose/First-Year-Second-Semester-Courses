window.onload = function(){
  document.body.style.height = screen.height + 'px';
  document.body.addEventListener("click", function(event){
    var coordX = event.pageX;
    var coordY = event.pageY;
    var divNou = document.createElement("div");
    divNou.classList.add("animat");
    var merge = document.body.appendChild(divNou);
    merge.style.position = "relative";
    merge.style.top = coordX;
  })


}
