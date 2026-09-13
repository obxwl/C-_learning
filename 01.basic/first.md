# C 语言与 GitHub 学习记录

## 1. 学习目标与环境

当前目标：学习 C 语言，同时通过保存练习代码掌握 Git 和 GitHub。

已有软件：
- VS Code
- Visual Studio
- Git

已有硬件：
- 野火 STM32F103C8T6 套件
- 树莓派
- 小车控制主板

当前先在电脑上学习 C，后续再用 STM32 做实践。

C 语言学习顺序：
基本语法 → 条件与循环 → 函数 → 数组与字符串 → 指针 → 结构体 → 多文件组织 → 位运算。

参考资源：
- 浙江大学 C 语言课程：https://www.icourse163.org/course/ZJU-199001
- Exercism C：https://github.com/exercism/c
- TheAlgorithms C：https://github.com/TheAlgorithms/C

## 2. 本次完成的成果

- 创建仓库：https://github.com/obxwl/C-_learning
- 克隆仓库到电脑。
- 编写 hello.c。
- 生成 SSH 密钥，将公钥添加到 obxwl。
- 配置 SSH 通过 Clash 连接 GitHub。
- 成功上传第一次本地提交。

本地仓库位置：
C:\Users\qzc\Desktop\C\C-_learning

上传成功的输出：

```text
cd4e00b..b621db2  main -> main
```

## 3. Git 与 GitHub 的区别

Git：管理电脑上的代码版本。
GitHub：保存远程仓库，提供协作和代码审查等功能。

需要区分三个身份：

- VS Code 登录账号：用于设置同步、扩展等。
- Git 提交署名：由 user.name 和 user.email 设置。
- Git 上传认证账号：决定是否有权限上传到目标仓库。

修改 user.name 不能切换上传认证账号。

## 4. 遇到的问题

### 不在仓库目录

报错：

```text
fatal: not a git repository
```

解决：进入仓库后再执行 Git 命令。

```powershell
cd C:\Users\qzc\Desktop\C\C-_learning
git status
```

### Git 无法连接 GitHub

浏览器能访问，但 Git 出现连接超时或连接重置。

使用的代理工具：Clash for Windows。
本地代理端口：7890。

通过指定代理成功克隆：

```powershell
git -c http.proxy=http://127.0.0.1:7890 clone https://github.com/obxwl/C-_learning.git
```

### 上传身份不匹配

报错：

```text
Permission to obxwl/C-_learning.git denied to wjqzc
```

说明 Git 上传时使用的认证身份是 wjqzc，没有目标仓库的写入权限。

尝试浏览器和设备验证码认证时，登录管理器多次连接中断。
网页显示授权成功，不代表终端已成功保存凭据或上传代码。

最终使用 SSH，成功认证为 obxwl，并完成上传。

### 将配置内容当成命令执行

Host、User、Port 等是 SSH 配置文件内容。
它们需要写入 config 文件，不能直接在 PowerShell 中执行。

## 5. SSH 密钥

私钥：
C:\Users\qzc\.ssh\github_obxwl

公钥：
C:\Users\qzc\.ssh\github_obxwl.pub

注意：
- 公钥添加到 GitHub。
- 私钥留在电脑上，不能上传或发送给别人。
- 私钥保护口令由自己设置，不是 GitHub 密码。
- 同一台电脑可以继续使用现有密钥，无需为每个仓库重新生成。

生成密钥时使用的命令：

```powershell
New-Item -ItemType Directory -Force -Path "$env:USERPROFILE\.ssh"
ssh-keygen -t ed25519 -C "obxwl-github" -f "$env:USERPROFILE\.ssh\github_obxwl"
```

以上只是记录，不要再次执行并覆盖现有密钥。

复制公钥到剪贴板：

```powershell
Get-Content "$env:USERPROFILE\.ssh\github_obxwl.pub" | Set-Clipboard
```

GitHub 添加入口：
https://github.com/settings/keys

选择 New SSH key：
- Title：自定义电脑名称。
- Key type：Authentication Key。
- Key：粘贴公钥完整内容。

## 6. 当前 SSH 配置

配置文件：
C:\Users\qzc\.ssh\config

文件名是 config，没有 .txt 后缀。

文件内容：

```sshconfig
Host github.com
    HostName ssh.github.com
    User git
    Port 443
    IdentityFile ~/.ssh/github_obxwl
    IdentitiesOnly yes
    ProxyCommand "E:/Program Files/Git/mingw64/bin/connect.exe" -H 127.0.0.1:7890 %h %p
```

作用：
使用专用密钥，通过 Clash 的 7890 代理端口，连接 GitHub 的 SSH 443 端口。

测试命令：

```powershell
ssh -T git@github.com
```

成功输出：

```text
Hi obxwl! You've successfully authenticated, but GitHub does not provide shell access.
```

“不提供 shell access”是正常提示，不影响 Git 操作。

当前仓库已切换为 SSH：

```powershell
git remote set-url origin git@github.com:obxwl/C-_learning.git
```

后续 push、pull、fetch 都通过 SSH。
需要保持 Clash 运行。
提示 Enter passphrase 时，输入私钥保护口令。

## 7. 日常提交流程

先修改并保存文件，在仓库根目录执行：

```powershell
git status
git diff
git add "01.basic/hello.c"
git diff --staged
git commit -m "说明这次修改了什么"
git push
```

文件路径要按实际位置修改。

各命令作用：
- git status：查看新增、修改和暂存状态。
- git diff：查看尚未暂存的已跟踪文件修改。
- git add：选择本次准备提交的改动。
- git diff --staged：检查暂存内容，包括新文件。
- git commit：保存为本地版本。
- git push：上传本地提交到 GitHub。

新文件在暂存前通常不显示在普通 git diff 中。
如果进入翻页界面，按 q 退出。

## 8. 如何快捷获取文件路径

方法一：
在 VS Code 左侧右键文件，选择“复制相对路径”。
粘贴到 git add 后面。

方法二：
在终端输入路径前几个字符，按 Tab 补全。

路径含空格时，加双引号：

```powershell
git add "文件夹名称/文件名称.c"
```

在仓库根目录暂存全部改动：

```powershell
git add .
```

这会暂存当前目录及子目录中的新增、修改和删除。
使用前先检查 git status，避免加入无关文件。

撤销某个文件的暂存：

```powershell
git restore --staged "01.basic/hello.c"
```

这只撤销暂存，保留文件内容。

## 9. 忽略编译产物

在仓库根目录创建 .gitignore，可填写：

```gitignore
.vs/
Debug/
Release/
x64/
*.exe
*.obj
*.pdb
*.ilk
```

源码和必要项目配置应保留，编译产物通常不用上传。
.gitignore 不会自动取消对已经跟踪文件的跟踪。

## 10. 其他仓库复用现有密钥

推荐直接使用 SSH 地址克隆：

```powershell
git clone git@github.com:obxwl/仓库名.git
cd 仓库名
```

如果已经用 HTTPS 克隆，进入该仓库，修改远程地址：

```powershell
git remote set-url origin git@github.com:obxwl/仓库名.git
```

查看当前远程地址：

```powershell
git remote -v
```

能克隆，不代表能上传：
- 自己的仓库：可以直接上传。
- 别人的仓库：需要写入权限。
- 参与别人的开源项目：通常先 Fork，再克隆自己的 Fork，修改后通过 PR 贡献。

每个仓库独立管理版本，操作前确认终端位置和远程地址。

## 11. 保存这份笔记并提交

将本笔记保存为：
notes/git-learning.md

在仓库根目录执行：

```powershell
git add notes/git-learning.md
git diff --staged
git commit -m "记录 Git 和 SSH 配置学习过程"
git push
```

## 12. 下一步

- 继续学习 C 语言。
- 每完成一个明确的小练习或修复，提交一次。
- 后续练习分支、Pull Request、合并与拉取更新。