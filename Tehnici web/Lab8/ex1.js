function creare()
{
  function innegrire(buton, e, i)
  {
    if (e.key == i)
    {
      buton.classList.remove("cifra" + i);
      buton.classList.add("negru");
    }
  }
  function laNormal(buton, e, i)
  {
    if (e.key == i)
    {
      buton.classList.remove("negru");
      buton.classList.add("cifra" + i);
    }
  }

  for (let i = 0; i < 10; i++)
  {
    let buton = document.createElement("button");
    document.querySelector("body").appendChild(buton);
    buton.innerHTML = i;
    buton.classList.add("copil", "cifra" + i);

    window.addEventListener("keydown", function(e){innegrire(buton, e, i)});
    window.addEventListener("keyup", function(e){laNormal(buton, e, i)});
  }
}

creare();
