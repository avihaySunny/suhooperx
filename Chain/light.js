window.onload = function() {
    const canvas = this.document.createElement("canvas"); 
    const context = canvas.getContext("2d");
    
    canvas.width  = 1920;
    canvas.height = 1080;
    canvas.style.marginTop = `${((window.innerHeight / 2) - (canvas.height / 2))}px`;
    
    // styles -------------------------
    document.body.style.background = "#000000";
    canvas.style.background = "#111111";
    canvas.style.display = "block";
    canvas.style.margin = "0 auto";
    // --------------------------------- 

    function Ray(x, y, angle){
        this.x = x; 
        this.y = y; 
        this.angle = angle; 

        this.drawRay = function(){
            context.beginPath();  
            context.lineTo(this.x, this.y); 
            context.fill(); 
        }
    }

    var myray = new Ray(100,100, 0);
    myray.drawRay();  

}