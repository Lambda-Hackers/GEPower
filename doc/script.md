### Data Structure
This doc put emphasis on the discussion at **Data Structure** of the script which wrote by Lua

```lua
{
	-- 精灵Id，底层生成唯一，string
	Id = "Snake_1"
	-- 名称，可选
	Name = "Snake",

	-- 不是所有的“精灵”都有动作，是一个可选的模块
	Action = {
		-- 每 1 帧刷新一次动作
		speed = 1, -- int，默认值 = “游戏设置”（全局设置）的几倍
		-- 动作数据
		ac = {
			move_right
		},
		-- 动作模式 目前有 Loop Rand
        -- Loop：循环ac数据结构中的所有函数
        -- Rand：每次随机选取ac数组中的一个函数进行操作
        -- 1, 2, 3, 4 ... 重复执行ac中的编号函数
		mode = "Loop"
	},

	-- 不是所有的“精灵”都有模型，是一个可选的模块
	Model = {
		"1D" : {
			point_x = 0,
			point_y = 0
		},
		"2D" : {
			-- ...
			model = "line"
			
		}
	}

	-- 不是所有的“精灵”都有需要对外部反应，是一个可选的模块
	React = {
		-- 绑定当前“精灵”对外界按键A,D输入响应函数为funcLift，funcRight
		-- function 无参数，无返回值
		Input_A = funcLift,
		Input_D = funcRight,
		-- 绑定当前“精灵”对外界按键所有按键和所有剩余按键的响应函数
		-- function 有一个参数 string，无返回值
		Input_All = funcAll,
		Input_Else = funcElse,

		-- 绑定当前“精灵”对碰撞事件的响应函数
		preCrash = {
			-- 在碰撞时需要获取的参数，以下为所有可选
			-- x，y，z 坐标
			"point_x",
			"point_y",
			"point_z",
			-- 当前时间
			"time",
			-- 当前碰撞物体
			"id",
			-- 自定义数据，从全局表中获取
			"Globle.goal"
		}
		-- function 有一个参数 table（preCrash），无返回值
		crash = funCrash,

		-- 自定义事件，如自定义消息
		-- 参数个数和类型由定义者决定，当给定参数不够时 nil 填充
		soundEnd = soundEndFunc
	}
}
```



