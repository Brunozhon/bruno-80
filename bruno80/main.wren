class Game {
    static update() {
        Bruno80.clearScreen()
        
        var key = Bruno80.getKey()
        System.print(key)
        if (key == Bruno80.keyCodeW) Bruno80.draw(1, 1, 255, 255, 255)
    }
}