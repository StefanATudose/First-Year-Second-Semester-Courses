window.onload = function(){
  document.getElementsByTagName("button")[0].addEventListener("click", function(event){
    var artNou = document.createElement("article");
    var dataTrimitere = new Date;
    dataTrimitere = "<span>" + dataTrimitere.getDate() + "-" + dataTrimitere.getMonth() + "-" + (1900+dataTrimitere.getYear()) + "</span>";
    artNou.innerHTML = "<h3>" + dataTrimitere + ": " + document.getElementById("titlu").value + "</h3><p>" + document.getElementById("post").value +  "</p>";
    artNou.classList.add("post");
    document.getElementById("postari").appendChild(artNou);
    var articole = document.getElementsByTagName("article");
    for (i = 0; i < articole.length; i++){
      articole[i].addEventListener('click', function(){
        this.remove();
      })
    }
  });
}
