window.onload = function() {
    const canvas = this.document.createElement("canvas"); 
    const context = canvas.getContext("2d");
    context.width = 500;
    context.height = 800;
    const dt = 0.1; // time in millisec
    const g = -9.81; 
    const colors = ["#00fffb", "#ff0062", "#a253c9", "#a5b56b", "#d2fae3"];
    var onFloor = false; 

    canvas.style.marginTop = `${((window.innerHeight / 2) - (canvas.height / 2))}px`;
    
    // styles -------------------------
    document.body.style.background = "#000000";
    canvas.style.background = "#111111";
    canvas.style.display = "block";
    canvas.style.margin = "0 auto";
    // --

    function Ball(x, y , radius){
        this.x = x; 
        this.y = y; 
        this.radius = radius; 
        this.speed = 0; 
        this.color = colors[parseInt(Math.random() * colors.length)]; 
        this.mass = 1;  
    
        this.ke = ()=>{ 
            return 0.5 * this.mass * this.speed * this.speed;  
        }
    }

    function Wall(x, y, height, width){
        this.x = x; 
        this.y = y; 
        this.heigh = height; 
        this.
    }
    
    function draw(ball){
        var context = document.getElementById("canvas").getContext("2d");  
        context.clearRect(0,0, 500,500);
        context.beginPath(); 
        context.fillStyle =  ball.color; 
        context.arc(ball.x, ball.y, ball.radius, 0, 2*Math.PI, true);
        context.fill(); 
    
    }
    
    var ball = new Ball(150, 200, 25);   

    const tick = function() {
        update(); 
        if (onFloor != true){
            draw(ball); 
            requestAnimationFrame(tick);
        }
    }

    function update(){
        if (onFloor != true){
        ball.speed -= g*dt; 
        ball.y +=  ball.speed*dt - 0.5*g*dt*dt; 
       // console.log(ball.ke());
        //reached the floor ? 
        if (ball.y +  ball.radius > 500){
            var c = 0.05; 
            ball.speed = -ball.speed * (1 - c);
            ball.color =colors[ parseInt(Math.random() * colors.length) ];   
        }
        
        }
    }

    tick(); 
}