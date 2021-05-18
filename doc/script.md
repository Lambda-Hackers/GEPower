### Data Structure
This doc put emphasis on the discussion at **Data Structure** of the script which wrote by Lua

```lua
{
	-- 名称，可选
	Name = "Snake",

	-- 不是所有的“精灵”都有动作，是一个可选的模块
	Action = {
		-- 每 1 帧刷新一次动作
		"speed" = 1, -- int，默认值 = “游戏设置”（全局设置）的几倍
		-- 动作数据
		ac = {
			
		},
		-- 动作模式 
		mode = "Loop"
	}
}
```



