  var lienzoElement = document.getElementById("plano");
  var dom = document.getElementById('body');
  var lienzo = lienzoElement.getContext("2d");
  var distancias = [150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80,150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80]
  var angulos =[180,90,0,45,140,123,15,50,60]
  var i = 0;
  const urlB = ["RadarRojo","RadarVerde","RadarAzul"];
  const primarie = ["#b10424","#04B123","#12BAFD"];
  const secundarie = ["#580C1D","#006412","#0F5E7E"];
  document.getElementById("Changer").addEventListener("click",function(){
    console.log("changing");
    i++;
    if(i>2){
      i=0;
    }
    fondo.url = `https://ricardoromo.co/Rbot/${urlB[i]}.png`;
    fondo.imagen = new Image();
    fondo.imagen.src = fondo.url;
    fondo.imagen.addEventListener("load",dibujarFondo);
    dom.style.background =`linear-gradient(${primarie[i]}, ${secundarie[i]})`;
  })


  var fondo = {
    url:`https://ricardoromo.co/Rbot/${urlB[i]}.png`,
    cargaOK:false
  };
  fondo.imagen = new Image();
  fondo.imagen.src = fondo.url;
  fondo.imagen.addEventListener("load",dibujarFondo);

  setInterval(()=>{
    rastreador()
  },200)

  function dibujarFondo() {
    fondo.cargaOK=true;
    dibujar();
  }
  function dibujar(){
    if (fondo.cargaOK){
        lienzo.drawImage(fondo.imagen,0,0);
    }
  }
  function rastreador() {
    dibujarFondo()
    lienzo.beginPath();
    distancias.sort(function(a, b){return 0.5 - Math.random()});
    for (var dist in distancias) {
      let tetha = (dist*5)*Math.PI/180;
      let x = distancias[dist]*Math.cos(tetha)+lienzo.canvas.width/2
      let y  = -distancias[dist]*Math.sin(tetha) +lienzo.canvas.height
      //console.log(`Distancia [${dist}]: ${distancias[dist]} - Angle: ${tetha}`);
      //console.log(`X: ${x} - Y: ${y}`);
      dibujante(lienzo.canvas.width/2, x , lienzo.canvas.height, y , "white");
    }
  }

  function dibujante( xi, xf, yi, yf, colorLine){
    lienzo.beginPath();
    lienzo.lineWidth = 3;
    lienzo.lineCap="round";
    lienzo.strokeStyle=colorLine;
    lienzo.moveTo(xf+1,yf+1);
    lienzo.lineTo(xf,yf);
    lienzo.stroke();
    lienzo.closePath();
  }

  window.onbeforeunload = function(e) {
  return WS_close();
  };

  // var lienzoElement = document.getElementById("plano");
  // var lienzo = lienzoElement.getContext("2d");
  // var distancias = [150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80,150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80]
  // var angulos =[180,90,0,45,140,123,15,50,60]
  //
  // function rastreador(angle,size) {
  //   distancias[angle]=size;
  //   lienzo.beginPath();
  //   lienzo.rect(0, 0, 300, 300);
  //   lienzo.fillStyle = "black";
  //   lienzo.fill();
  //   lienzo.closePath();
  //   //distancias.sort(function(a, b){return 0.5 - Math.random()});
  //   for (var dist in distancias) {
  //     let tetha = (dist*5)*Math.PI/180;
  //     let x = distancias[dist]*Math.cos(tetha)+150
  //     let y  = -distancias[dist]*Math.sin(tetha) +300
  //     //console.log(`Distancia [${dist}]: ${distancias[dist]} - Angle: ${tetha}`);
  //     //console.log(`X: ${x} - Y: ${y}`);
  //     dibujante(150, x , 300, y , "yellow");
  //   }
  // }
  //
  // function dibujante( xi, xf, yi, yf, colorLine){
  //   lienzo.beginPath();
  //   lienzo.strokeStyle=colorLine;
  //   lienzo.moveTo(xi,yi);
  //   lienzo.lineTo(xf,yf);
  //   lienzo.stroke();
  //   lienzo.closePath();
  // }
