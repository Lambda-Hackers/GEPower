--[[local function snake_crash()

end

function script_run()
    local snakeTable = {
        name = "snake",
        point = {
            x = 0,
            y = 0
        }
    }
    local snake = create(snakeTable)
    -- snake.bind("CRASH", snake_crash, {"ordinate", "mutual", "time"})
    snake.bind("CRASH", snake_crash)
end
]]--
print("xxxxxxxxxxxxxxxxx\n");