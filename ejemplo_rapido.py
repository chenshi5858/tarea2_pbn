import turtle

# Configuración inicial
t = turtle.Turtle()
t.speed(0)
t.color("black")

# Cuerpo del pingüino
t.penup()
t.goto(0, -150)
t.pendown()
t.begin_fill()
t.color("black")
t.circle(100)
t.end_fill()

# Cabeza del pingüino
t.penup()
t.goto(0, -50)
t.pendown()
t.begin_fill()
t.color("black")
t.circle(50)
t.end_fill()

# Ojos
t.penup()
t.goto(-20, 0)
t.pendown()
t.begin_fill()
t.color("white")
t.circle(20)
t.end_fill()
t.penup()
t.goto(-20, 10)
t.pendown()
t.color("black")
t.begin_fill()
t.circle(10)
t.end_fill()
t.penup()
t.goto(20, 0)
t.pendown()
t.begin_fill()
t.color("white")
t.circle(20)
t.end_fill()
t.penup()
t.goto(20, 10)
t.pendown()
t.color("black")
t.begin_fill()
t.circle(10)
t.end_fill()

# Pico
t.penup()
t.goto(0, -50)
t.pendown()
t.goto(0, -70)
t.goto(20, -50)
t.goto(0, -50)

# Pies
t.penup()
t.goto(-30, -150)
t.pendown()
t.begin_fill()
t.color("orange")
t.circle(20, 180)
t.left(90)
t.forward(40)
t.left(90)
t.circle(20, 180)
t.end_fill()

# Ocultar la pluma
t.hideturtle()

# Terminar dibujo
turtle.done()
