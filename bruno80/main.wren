class Entity {
    y=(value) { _y = value }
    y { _y }

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
}

var Height = Bruno80.screenHeight
var Width = Bruno80.screenWidth

// Paddles
var PaddleA = Entity.new(0, Height / 2 - 15, 2, 30, 255, 255, 255)
var PaddleB = Entity.new(Width - 2, Height / 2 - 15, 2, 30, 255, 255, 255)

class Game {
    static update() {
        Bruno80.clearScreen()
        
        var key = Bruno80.getKey()
        if (key == Bruno80.keyCodeW && PaddleA.y > 1) PaddleA.y = PaddleA.y - 2
        if (key == Bruno80.keyCodeS && PaddleA.y < Height - PaddleA.height - 1) PaddleA.y = PaddleA.y + 2

        PaddleA.draw()
        PaddleB.draw()
    }
}