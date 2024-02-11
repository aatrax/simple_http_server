
let alg_list = `<ul class="article-list">
<li class="article-item" >   
    <h2 class="article-title" onclick="openLink('doc/findthemax.html')">leetcode刷题:Find the Maximum Number of Elements in Subset</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/aliceandbob.html')">leetcode刷题:Alice and Bob Playing Flower Game</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/jumpgame2.html')">leetcode刷题:Jump Game 2</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/jumpgame.html')">leetcode刷题:Jump Game</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/besttimetobuy2.html')">leetcode刷题:Best Time to Buy and Sell Stock II</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/rotatearray.html')">leetcode刷题:Rotate Array</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/removeduplicates.html')">leetcode刷题:Remove Duplicates from Sorted Array II</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >
<li class="article-item" >
    <h2 class="article-title" onclick="openLink('doc/hindex.html')">leetcode刷题:H-index</h2>
    <p class="article-meta"> 发布时间：2024-02-05</p>
    <p class="article-content">难度：中等</p>
</li >

</ul > `
let list=document.querySelector('.article-list');
let content = document.querySelector("body");
let icon = document.querySelector('#moon');
let currentImage = content.style.backgroundImage;
let maindialog = document.querySelector("#dialog");
let redbird = document.getElementById("redbird");
let redbird_click=0;//红鸟被点击的次数
let dialogs = document.querySelectorAll(".dialog");
let blackbird = document.querySelector('#blackbird');
let blacknum = 0;//黑鸟的谈话
let blackdialog = document.querySelector('#blackdialog');
let goodboy = document.querySelector('#goodboy');
let int_bird;
let int_diag;
list.innerHTML=alg_list;
content.style.backgroundImage = 'url(bluesky.jpg)';
function toggleBackgroundColor() {

    // 切换背景图片
    currentImage = content.style.backgroundImage;
    if (currentImage.includes('bluesky.jpg')) {
        content.style.backgroundImage = 'url(darksky.jpg)';
        icon.className="fa-regular fa-moon";
    } else {
        content.style.backgroundImage = 'url(bluesky.jpg)';
        icon.className="fa-solid fa-moon";
    }
}

function openLink(url) {
    window.open(url, '_blank');
}

function showDialog(dialog) {
    currentImage = content.style.backgroundImage;
    if(currentImage.includes('bluesky.jpg')){
        maindialog.innerHTML="太亮了！";
    }else{
        maindialog.innerHTML="太暗了！";
    }
    dialog.style.display = "block";
    setTimeout(function() {
        hideDialog(dialog);
    }, 1000);
}

function hideDialog(dialog) {
    dialog.style.display = "none";
}

function showGif() {
    redbird = document.getElementById("redbird");
    redbird.src = "redbird.gif";
    setTimeout(function() {
        pauseGif();
    }, 1000);
}

function pauseGif() {
    redbird = document.getElementById("redbird");
    redbird.src = "static_redbird.gif"; // 暂停 GIF 图片
}

function redbirdevent() {

    var dialogs = document.querySelectorAll(".dialog");

    // 每隔2秒显示一次对话框
    int_diag=setInterval(function() {
        dialogs.forEach(function(dialog) {
            showDialog(dialog);
        });
    }, 4000);

    // 每隔5秒切换一次 GIF 图片
    int_bird=setInterval(function() {
        showGif();
    }, 4000);
}

document.addEventListener("DOMContentLoaded", redbirdevent);
function redbirdclick(){
    clearInterval(int_bird);
    clearInterval(int_diag);
    if(redbird_click==0)
    {
        maindialog.innerHTML="我是傻子吗？";
        dialogs.forEach(function(dialog){
        dialog.style.display = "block";
        setTimeout(function() {
        hideDialog(dialog);
        }, 3000);
        });
        redbirdevent();
        redbird_click++;
        return;
    }
    if(redbird_click==1)
    {
        maindialog.innerHTML="我有点神经质";
        dialogs.forEach(function(dialog){
        dialog.style.display = "block";
        setTimeout(function() {
        hideDialog(dialog);
        }, 3000);
        });
        redbirdevent();
        redbird_click++;
        return;
    }
    if(redbird_click==2)
    {
        maindialog.innerHTML="我一直在看着你";
        dialogs.forEach(function(dialog){
        dialog.style.display = "block";
        setTimeout(function() {
        hideDialog(dialog);
        }, 3000);
        });
        redbirdevent();
        redbird_click++;
        return;
    }
    if(redbird_click>2&redbird_click<6)
    {
        maindialog.innerHTML="滚开！";
        dialogs.forEach(function(dialog){
        dialog.style.display = "block";
        setTimeout(function() {
        hideDialog(dialog);
        }, 3000);
        });
        redbirdevent();
        redbird_click++;
        return;
    }
    if(redbird_click==6)
    {
        maindialog.innerHTML="你会受到到惩罚";
        dialogs.forEach(function(dialog){
        dialog.style.display = "block";
        setTimeout(function() {
        hideDialog(dialog);
        }, 3000);
        });
        redbird.src='';
        setTimeout(blackbird_emerge,2000);
        redbird_click++;
        return;
    }
}
redbird.addEventListener('click',redbirdclick)

function blacktalk(){
    blackdialog.style.display='block';
    blackdialog.innerHTML='咕嘟咕嘟';
    setInterval(function(){
        if(blacknum==0)
        {
            blackdialog.innerHTML='你好，刚才那是我弟弟，他有点神经，总是爱乱叫';
            blacknum++;
            return;
        }
        if(blacknum==1)
        {
            blackdialog.innerHTML='我替他道歉，我们是宠物鸟，主人和他的孩子很喜欢和我们一起玩';
            blacknum++;
            return;
        }
        if(blacknum==2)
        {
            blackdialog.innerHTML='看，主人的孩子来了,有时候我觉得他像一个布娃娃';
            goodboy.src='goodboy.gif';
            blacknum++;
            return;
        }
        if(blacknum==3)
        {
            blackdialog.innerHTML='哈哈，它既脆弱又。。。恶心，哈哈';
            blacknum++;
            return;
        }
        if(blacknum==4)
        {
            blackdialog.innerHTML='哈哈，你觉得恶心吗';
            blacknum++;
            return;
        }
        if(blacknum==5)
        {
            blackdialog.innerHTML='有时候决定一个人的命运在另一个人手上的时候。。。';
            blacknum++;
            return;
        }
        if(blacknum==6)
        {
            blackdialog.innerHTML='有的人对于小事斤斤计较，但对大事过于随意，因为他脑子不够';
            blacknum++;
            return;
        }
        if(blacknum==7)
        {
            blackdialog.innerHTML='神经质的人就是这样，这是遗传，我在克服。。。';
            blacknum++;
            return;
        }
        if(blacknum==8)
        {
            blackdialog.innerHTML='你觉得另一个人的生死是大事吗，哈哈';
            blacknum++;
            return;
        }
        if(blacknum==9)
        {
            blackdialog.innerHTML='我追求美与真理，无法容忍令我恶心的事';
            blacknum++;
            return;
        }
        if(blacknum==10)
        {
            blackdialog.innerHTML='嗯。。咱来玩个游戏吧，你最喜欢的数字是什么';
            setTimeout(function(){let num=prompt('你最喜欢的数字');
            if(num==9)
            {
                window.location.href='gift.html';
            }
            else{
                window.location.href='horror.html';
            }},1000)
            blacknum++;
            return;
        }
    },4000);
}
function blackbird_emerge(){
    blackbird.src="blackbird.gif";
    setTimeout(function(){
        blackbird.src="static_blackbird.gif";
    },1000);
    setTimeout(blacktalk, 1000);
}
