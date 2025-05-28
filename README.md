# 投篮机器人仿真实验


---
## BaseSetting

* **场地**
	* Rectangle:    $( 0mm , 0mm )$ --> $( 10000mm , 10000mm )$
	* G:    $9800 mm/s^2$

* **篮筐**
	* **Position**:    $( 10000mm , 5000mm , 2000mm )$
	* Area:    ${(132mm)}^2*\pi$

* **机器**
	* Stating Position:    $( 0mm, 0mm )$
	* Movement Speed:    $1000{mm/s}$
	* **Maximum** Shooting Rate:    $15000mm/s$
	* Shooting **Delay**:    $22ms - 35ms$
	* **Range** of Motion
		* **Pitch** Angle:   起于 $xoy$平面  向 $z$轴 正方向 $5^{\circ} - 90^{\circ}$
		* **Rotation** Angle:    起于 $y$轴正方向 向 $y$轴负方向  $0^{\circ} - 180^{\circ}$

* **投篮区域**
	* Rectangle:    $( 4500mm , 4500mm )$ --> $( 5500mm , 5500mm )$

---
## Shooting Process 

1. 场地生成投篮位置点

2. 机器进入发射流程
	* 移动至位置点
	* **瞄准**
	* **投篮**
		* 发出投篮指令
		* **抖动**
		* **实际投篮**

3. 篮球斜抛 直至击中 $x=10000mm$平面 

4. 篮筐击中**检查**

---
## Appendix

1. `.vscode`目录下为vscode中调试配置文件，使用其它IDE可无视该目录内容。

2. `ShootMachine_Static`目录下实现机器**静止状态**下的投篮。

3. `ShootMachine_DynStaMix`目录下实现机器**运动状态**下的投篮。
	* 机器默认**只以最大速度移动**，到达位置点即发出投篮指令并在抖动时间内**位置偏移**
	* 未考虑多发射任务下机器的转向问题，即向新的位置点移动时**速度矢量方向骤变**

4. `ShootMachine_DynStaMix`为运动-静止混合版本，保留了静止投篮方法，完全囊括了`ShootMachine_Static`目录内容。