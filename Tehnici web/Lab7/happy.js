
function joc()
{
  window.onkeydown = function()
  {
    window.onkeydown = null;
    document.querySelector("#game p").style.visibility = "visible";
    for (var i = 0; i < 40; i++)
    {
      let imagine = document.createElement("img");
      imagine.src = "sad.png";
      document.querySelector("#container").appendChild(imagine);
    }
    var count = 0;
    var imagini = document.querySelectorAll("img");
    function plusscor()
    {
      this.src = "happy.png";
      count = count + 1;
      document.querySelector("#scor").innerHTML = count;
      this.removeEventListener("click", plusscor);
      }

    for (var ob of imagini)
    {
    ob.addEventListener("click", plusscor);

    }

    window.setTimeout(function(){
      var poze = document.querySelector("#container");
      poze.remove();
      var titlu = document.querySelector("h1");
      titlu.innerHTML = "Jocul s-a terminat! Scorul dumneavoastra a fost " + count;
    }, 5000);
  }
}



joc();
