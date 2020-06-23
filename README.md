<!--
 * @This File is Part of Sakura by SaeruHikari: 
 * @Description: Copyright SaeruHikari
 * @Version: 0.1.0
 * @Autor: SaeruHikari
 * @Date: 2020-03-01 20:09:10
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2020-06-17 00:28:49
 -->
[简体中文](./README.md) | [English](./README.en-US.md) | [文档](https://saeruhikari.github.io/SakuraEngine/#/)
<h1 align="center">Sakura Engine</h1>
<div align="center">

跨平台的现代游戏引擎 
</div>

![Sakura-Icon](Icons/Sakura-Icon.jpeg)

# 重构中
- virtual_filesystem: 可以挂载至多种文件系统下(local, packed, network...), 支持自定义的挂载手段;
- CGD => Painter: 更加合理且易用的API, 类Metal的接口;
- SHT: 代码生成器重构中, 完成parser替换以及架构重设计后会并入引擎工具目录。

# 特性
- 🌉 跨平台: Win32, Linux, Android(待定)以及IOS(待定)的跨平台基础支持;
- ⚙️ 模块/插件化: 基于依赖图的模块管理器[SPA](SPA/), 支持静态/动态导出的插件/模块;
# 不完全的支持
- 🧰 跨图形接口(Vulkan Only): [CGD](SakuraEngine/StaticBuilds/Graphicsinterface/)(CommonGraphicsDevice)现代图形API([Direct3D12](SakuraEngine/StaticBuilds/Graphicsinterface/CGD_Direct3D12/), [Vulkan](SakuraEngine/StaticBuilds/Graphicsinterface/CGD_Vulkan/))的上层抽象;

# Coming Soon
- 🎨 渲染调度: RenderGraph, 数据驱动可自由配置装载的Pass;

# 待实现
- 🖼️ 渲染特性: 字体渲染, RayTracing Layer, F+ Pipeline, 粒子...
- 📂 资产管理: 支持虚拟路径挂载, 资源依赖以及异步读取的资产管理系统;
- ⛳ 场景: 基于Node的场景管理, 提供自由的装载/序列化;


# 简介
&emsp;&emsp;SakuraEngine作为我的个人项目, 旨在提供一个易于扩展开发且跨平台的环境, 试验并实现各种游戏引擎技术。[文档](https://saeruhikari.github.io/SakuraEngine/#/)


## 1. Core
&emsp;&emsp;[Core](SakuraEngine/Core)的原旨是为开发提供关键字和基本工具, 并为跨平台开发提供基本系统操作接口。Core下包含了最小核心, 容器, 工具包以及数学库, 以及一些启动参数和核心状态。引入模块接口, 导出为CoreModule.dll。


## 2. StaticBuilds
&emsp;&emsp;为了降低引擎中的状态熵(即将状态向模块聚合, 再向少部分源文件聚合), SakuraEngine会提供很多静态构建的库来为模块提供功能, 同时用很少的源承载状态并于静态包链接。为了更深地了解这种思想, 您可以到[模块文档页](https://saeruhikari.github.io/SakuraEngine/#/Modules/)下进行了解。

### Painter
&emsp;&emsp;[Painter](SakuraEngine/StaticBuilds/Painter/)是一个现代图形API的抽象层。为了追求性能, Painter会彻底放弃对旧图形API的支持(D3D11/lower, OpenGL等)。

&emsp;&emsp;Painter仅仅是一层图形接口的抽象, 它的任务是跟进图形接口的特性, 并提供检查以及通用调用接口。引擎将会提供一个专门的模块调度Painter, 在此基础上进行渲染编程, 而非直接调度Painter进行渲染特性的实现。





## 3. 模块
&emsp;&emsp;为了以较低的心智负担维护并持续引擎的开发, 引擎将会完全模块化。提供模块管理器[SPA](SPA/)和一个完全无状态的静态[CoreModule](SakuraEngine/Core)模块, 其余功能全部导出共享库并模块化加载(当然静态模块也是支持的, 且容许其拥有状态)。

&emsp;&emsp;引擎以主模块为起点, 依依赖顺序加载并初始化所有的模块后, 从主模块的入口函数进入自定义程序循环。这也意味着引擎将会完全可装卸, 但需要额外留意版本控制。单元测试[SPAUnitTest](SPAUnitTest/)描述了一组简单的模块依赖图, 可以找到模块系统的示例。

&emsp;&emsp;模块均使用json进行版本和依赖的描述, 并在编译时将json描述元数据和插件接口一同编译进lib内, 这也意味着用户可以将任意的元数据编译进模块并在运行时取用。此外, 模块也支持运行时的属性附加及取用, 详情见[SPA](SPA/)。

&emsp;&emsp;以下内容均在[Modules](SakuraEngine/Modules)下作为扩展内容提供, 藉由SPA可以对它们进行自由的装卸来定制引擎功能组。默认地, 所有第一方提供的模块版本会跟随引擎自体的版本, 以此减轻版本控制的心智负担, 满足设计初期内容频繁变动的需求。

### Editor
&emsp;&emsp;[Editor](SakuraEngine/Editor)是引擎可执行文件的编译入口。对每个目标平台, Editor下都有其对应的主模块声明以及main函数入口实现。

### Render Graph
&emsp;&emsp;RenderGraph是Painter的调度层, 将会提供大量的方便接口来简化渲染编程。同时, Render Graph介入持久化/临时渲染资源的管理。RenderGraph将渲染依照Pass分离并节点化, 这也使得各个Pass可以独立地记录指令队列, 并在队列级别多线程化渲染任务。