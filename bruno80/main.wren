class Entity {
    x=(value) { _x = value }
    x { _x }

    y=(value) { _y = value }
    y { _y }

    width { _width }
    height { _height }

    construct new(x, y, width, height, r, g, b) {
        _x = x
        _y = y
        _width = width
        _height = height
        _r = r
        _g = g
        _b = b
    }

    draw() {
        for (i in 0..._width) {
            for (j in 0..._height) {
                Bruno80.draw(_x + i, _y + j, _r, _g, _b)
            }
        }
    }

    collidesWith(other) {
        return (_x < other.x + other.width) && (_x + _width > other.x) && (_y < other.y + other.height) && (_y + _height > other.y)
    }
}

var Height = Bruno80.screenHeight
var Width = Bruno80.screenWidth

// Paddles
var PaddleA = Entity.new(0, Height / 2 - 15, 2, 30, 255, 255, 255)
var PaddleB = Entity.new(Width - 2, Height / 2 - 15, 2, 30, 255, 255, 255)

// Ball
var Ball = Entity.new(Width / 2, Height / 2, 3, 3, 255, 0, 0)
var Dx = 1
var Dy = 1

class Game {
    static update() {
        Bruno80.clearScreen()
        
        var key = Bruno80.getKey()

        if (key == Bruno80.keyCodeW && PaddleA.y > 1) PaddleA.y = PaddleA.y - 2
        if (key == Bruno80.keyCodeS && PaddleA.y < Height - PaddleA.height - 1) PaddleA.y = PaddleA.y + 2

        if (key == Bruno80.keyCodeUp && PaddleB.y > 1) PaddleB.y = PaddleB.y - 2
        if (key == Bruno80.keyCodeDown && PaddleB.y < Height - PaddleB.height - 1) PaddleB.y = PaddleB.y + 2

        if (Ball.y + Dy <= 0 || Ball.y >= Height - Ball.height) Dy = -Dy
        
        if (Ball.x + Dx <= 0 || Ball.x + Dx >= Width - Ball.width) {
            Dx = 1
            Dy = 1
            Ball.x = Width / 2
            Ball.y = Height / 2
        }

        PaddleA.draw()
        PaddleB.draw()
        Ball.draw()

        Ball.x = Ball.x + Dx
        Ball.y = Ball.y + Dy

        if (Ball.collidesWith(PaddleA) || Ball.collidesWith(PaddleB)) Dx = -Dx
    }
}