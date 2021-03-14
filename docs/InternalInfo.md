# 开发信息跟踪

<style>
.testngppFeatureMap {
    text-align: center;
}
.testngppFeatureMap th {
background: lightgrey;
word-wrap: break-word;
text-align: center;
}
.testngppFeatureMap 
    tr:nth-child(1) 
    td:nth-child(n+3)                
    { background: lightgreen; }
.testngppFeatureMap 
    tr:nth-child(2) 
    td:nth-child(3)                
    { background: lightgreen; }
.testngppFeatureMap 
    tr:nth-child(2) 
    td:nth-child(4+n)                
    { background: red; }
.testngppFeatureMap tr:nth-child(3) { background: green; }
</style>

## 功能支持情况

### testngpp功能支持情况


<div class="testngppFeatureMap">

| OS  | 编译环境 | 基本功能 | 内存泄漏检查 | Sandbox执行 |
| ----  | ----  | ----  | ----        | ----       |
| Linux | GCC   | Yes   | Yes         | Yes        |
| Win10 | MinGW | Yes   | No          | No         |
| Win10 | VS2019 | Yes  | Maybe ①     | Yes        |
</div>

说明:
- testngpp基本功能包括
  - 自动生成用例辅助cpp文件，用例管理，用例运行，生成执行结果报告
- testngpp高级功能说明
  - 内存泄漏检查(without -m)：执行用例时检查是否有内存泄漏情况
  - Sandbox执行(with -s): 每个用例在单独沙箱运行，多用于持续集成 
- 表格填写状态说明
  - Yes : 支持
  - No : 不支持
  - Maybe : 可能支持(运行工具测试中发现一些异常，但不能确定用户环境是否可用)
- 注释
  - ①: testngpp用例执行时，三个测试套件报内存泄漏(TestMemChecker,TestXMLBuilder,TestXMTestLListener).


## 测试用例执行情况

|  项目   | OS  | 编译环境 | 用例执行(-m) | 用例执行 | 
|  ----  | ----  | ----  | ----  | ----  |
| mockcpp | Win10 | MinGW | All Pass | NA |
| testngpp| Win10 | MinGW | All Pass | NA |
| mockcpp | Win10 | VS2019 | All Pass | NA |
| testngpp| Win10 | VS2019 | All Pass | NA |


testngpp相关说明：
- 用例执行(-m) 表示执行用例时关闭内存检查。
- MinGW下的内存检查功能还未开通。
- 

mockcpp相关说明：
- 