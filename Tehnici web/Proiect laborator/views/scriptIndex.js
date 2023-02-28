var cheie = 0;
function aplicatie(){
  localStorage.clear();
  var recenzii = document.getElementsByClassName("recenzie");     ///manevrare DOM class
  for (i = 0; i < recenzii.length; i++)
    recenzii[i].addEventListener("click", adaugStorageColorez)        ///modificare stil elemente
}

function generare(event){
  let parinte = this.parentNode;
  var cadru = document.createElement("iframe");         ///creare elemente
  cadru.src = '/gol.html';                             ///modificare proprietati
  cadru.style.display = 'block';
  cadru.width = '100%';
  cadru.height = '800px';
  parinte.appendChild(cadru);
  var continutCadru = document.getElementsByTagName("iframe")[0].contentWindow;   ///manevrare DOM tags

  for (let i = 0; i < localStorage.length; i++){
    let cheiCurenta = localStorage.key(i);                              ///folosire local storage
    let sectiuneNoua = document.createElement("section");
    sectiuneNoua.innerHTML = localStorage.getItem(cheiCurenta);
    sectiuneNoua.getElementsByTagName("img")[0].style.height = window.getComputedStyle(document.querySelector(".recenzie img")).height;   ///folosire getComputedStyle
    continutCadru.document.getElementsByTagName("body")[0].appendChild(sectiuneNoua);
  }
  //this.removeEventListener('click', generare);
  //continutCadru.document.body.style.backgroundColor = "blue";     ///modificare eveniment mouse
}

document.getElementById("startApl").addEventListener('click', aplicatie);
document.getElementById("btnGenerare").addEventListener('click', generare);     ///manevrare DOM ID

function adaugStorageColorez(event){
  this.style.backgroundColor = "green";
  cheie += 1;
  localStorage.setItem(cheie, this.innerHTML);          ///folosire local storage
}
var iterator;
function daCuloareRandom(){                                         ///schimbare aleatoare de proprietati(culoare)
  let codRandCuloare = Math.floor(Math.random()* 0xFFFFFF);         ///metode clasa math
  codRandCuloare = codRandCuloare.toString(16);
  let randomCul = "#" + codRandCuloare.padStart(6, 0);
  return randomCul;
}

function schimbCuloare(ob){
  ob.style.backgroundColor = daCuloareRandom();
  ob.getElementsByTagName("h3")[0].classList.toggle("stelemari");             ///class list
}

var time, supriza2;

function surpriza1(event){
  if (event.key == '~'){
      let pauza = 0;
      let recenzii = document.querySelectorAll(".recenzie");            ///manevrare DOM selectorCSS
      for (iterator = 0; iterator < recenzii.length; iterator++){
          time = setTimeout(schimbCuloare, pauza+=100, recenzii[iterator]);       ///setTimeout
          time;
      }
  }
}

document.body.addEventListener('keydown', function(event){surpriza2 = setInterval(surpriza1, 1000, event)});  ///folosire eveniment tastatura; setInterval

function stergereRecenzii(){
  var recenzii = document.getElementsByClassName("recenzie");
  for (let i = 0; i < recenzii.length; i++){
    recenzii[i].removeEventListener("click", adaugStorageColorez)
    let parinte = recenzii[i].parentNode;
    recenzii[i].addEventListener("click", function(){
      recenzii[i].remove();
      i--;
    })
    let copii = recenzii[i].childNodes;
    for (let j = 0; j < copii.length; j++)
      copii[j].addEventListener("click", function(event){
          this.remove();
        j--;
        event.stopPropagation();                    ///stopPrpagation
      })
  }
}

document.getElementById("btnStergere").style.height = '20px';
document.getElementById("btnStergere").style.width = '300px';
document.getElementById("btnStergere").addEventListener('click', stergereRecenzii);


function posteaza(){
  event.preventDefault();
  var date = {nume: document.getElementById('nume').value, email: document.getElementById('mail').value,
   comment: document.getElementById('textComm').value};
   fetch('http://localhost:8080/postComm',{
     method: 'post',
     headers: {'Content-Type': 'application/json'},
     body: JSON.stringify(date)
   }).then(function(response){
     return response.text();
   }).then(function(text){
     var nouComm = document.createElement('p');
     nouComm.innerHTML = text;
     document.getElementById("comentarii").removeChild(document.getElementsByTagName("form")[0]);
     document.getElementById("comentarii").appendChild(nouComm);
   });
}

function validare(){
  //event.preventDefault();
  var deVerificat = document.getElementById("mail").value;
  var deModificat = document.getElementById("mail");
  var formatMail = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
  if (formatMail.test(deVerificat)){
    ///alert("comentariul este valid!");
    posteaza();
    return true;
  }
  else{
    alert("Introduceti va rog un mail valid!");{
      deModificat.focus();
      event.preventDefault();
      return false;
    }

  }
}

function addCommForm(event){
  let formular = document.createElement("form");
  formular.setAttribute('method', 'post');          ///setAttribute
  formular.setAttribute('action', 'http://localhost:8080/postComm');
  formular.innerHTML = "<label>Nume:</label>  \
<input type='text' name='name' id = 'nume'>  \
<br>  \
<label> Email</label> \
<input type='text' name='mail' id = 'mail'> \
<br> \
 <label>Comentariu:</label>  \
<textarea name = 'text' id = 'textComm'> Introdu textul: </textarea>\
<br>  \
<button type='submit' id='sendForm' > Trimite </button>";
  event.target.parentNode.appendChild(formular);
  document.getElementById('sendForm').addEventListener('click', validare);
}



document.getElementById("addComment").addEventListener("click", addCommForm)
