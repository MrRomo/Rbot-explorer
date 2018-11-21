  var lienzoElement = document.getElementById("plano");
  var lienzo = lienzoElement.getContext("2d");
  var distancias = [150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80,150,15,50,75,80,10,120,110,80,150,15,50,75,80,10,120,110,80,110,80]
  var angulos =[180,90,0,45,140,123,15,50,60]
  setInterval(()=>{
    rastreador()
  },200)
  function rastreador() {
    console.log("INNER");
    lienzo.beginPath();
    lienzo.rect(0, 0, 300, 300);
    lienzo.fillStyle = "black";
    lienzo.fill();
    lienzo.closePath();
    distancias.sort(function(a, b){return 0.5 - Math.random()});
    for (var dist in distancias) {
      let tetha = (dist*5)*Math.PI/180;
      let x = distancias[dist]*Math.cos(tetha)+150
      let y  = -distancias[dist]*Math.sin(tetha) +300
      console.log(`Distancia [${dist}]: ${distancias[dist]} - Angle: ${tetha}`);
      console.log(`X: ${x} - Y: ${y}`);
      dibujante(150, x , 300, y , "yellow");
    }
  }

  function dibujante( xi, xf, yi, yf, colorLine){
    lienzo.beginPath();
    lienzo.strokeStyle=colorLine;
    lienzo.moveTo(xi,yi);
    lienzo.lineTo(xf,yf);
    lienzo.stroke();
    lienzo.closePath();
  }
