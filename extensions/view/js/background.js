chrome.runtime.onInstalled.addListener(function(){
	chrome.contextMenus.create({
		type: 'normal',
		title: 'WebClipper',
		id: 'WebClipper',
		contexts: ['all'],
	});
	chrome.contextMenus.create({
		type: 'normal',
		title: '保存所选文本',
		id: 'SaveSelectedTxt',
		parentId: 'WebClipper',
		contexts: ['selection']
	});
	chrome.contextMenus.create({
		type: 'normal',
		title: '保存全部的文本',
		id: 'SaveWebText',
		parentId: 'WebClipper',
		contexts: ['all']
	});
	chrome.contextMenus.create({
		type: 'normal',
		title: '保存所选的图片',
		id: 'SaveWebImg',
		parentId: 'WebClipper',
		contexts: ['selection']
	});
	chrome.contextMenus.create({
		type: 'normal',
		title: '保存所选的网页',
		id: 'SaveSelectedWebPage',
		parentId: 'WebClipper',
		contexts: ['selection']
	});
	/*chrome.contextMenus.create({
		type: 'normal',
		title: '保存所选的链接',
		id: 'SaveWebPages',
		parentId: 'WebClipper',
		contexts: ['link']
	});*/
	chrome.contextMenus.create({
		type: 'normal',
		title: '保存网页',
		id: 'SaveWebPage',
		parentId: 'WebClipper',
		contexts: ['all']
	});
});

/*function translateGoogle(info, tab){
	var url = 'http://translate.google.cn/#auto/zh-CN/' + info.selectionText;
	window.open(url,'_blank');
}
function translateBaidu(info, tab){
	var url = 'http://fanyi.baidu.com/?aldtype=16047#zh/en/' + info.selectionText;
	window.open(url,'_blank');
}*/

var port = null;

function connect() {
  var hostName = "com.xiaowenwen.webclipper";
  //appendMessage("Connecting to native messaging host <b>" + hostName + "</b>")
  port = chrome.runtime.connectNative(hostName);
  port.onMessage.addListener(onNativeMessage);
  port.onDisconnect.addListener(onDisconnected);
}
function sendNativeMessage(data) {
  //message = {"text": document.getElementById('input-text').value};
  //message = {"text": data}
  message = data;
  port.postMessage(message);
  //alert(JSON.stringify(message));
  //appendMessage("Sent message: <b>" + JSON.stringify(message) + "</b>");
}

function onNativeMessage(message) {
  appendMessage("Received message: <b>" + JSON.stringify(message) + "</b>");
}

function onDisconnected() {
  appendMessage("Failed to connect: " + chrome.runtime.lastError.message);
  port = null;
}

function SaveSelectedTxt(info, tab){
	message = {"type": "SelectedTxt","URL":info.pageUrl,"title":tab.title,"data":info.selectionText};
	connect();
	sendNativeMessage(message);
}


function SaveWebText(info, tab){
	chrome.tabs.executeScript(tab.id, {file: 'view/js/FileTxtSaver.js'}, function(results){
      if (results){
      		message = {"type": "WebText","URL":info.pageUrl,"title":tab.title,"data":results};
        	connect();
			sendNativeMessage(message);
      }
    });
}

function SaveSelectedImg(info, tab){
	chrome.tabs.executeScript(tab.id, {file: 'view/js/ImgSaver.js'}, function(results){
      if (results){
      		message = {"type": "WebText","URL":info.pageUrl,"title":tab.title,"data":results};
        	connect();
			sendNativeMessage(message);
      }
    });
     /*chrome.tabs.executeScript(tab.id, {file: 'view/js/ImgSaver.js'}, function(results){
     if (results && results[0] && results[0].length){
        results[0].forEach(function(url) {
          chrome.downloads.download({
            url: url,
            //filename: Date() + Math.random(),
            conflictAction: 'uniquify',
            saveAs: true
          });
        });
      }*/
}

function SaveSelectedWebPage(info, tab){
	chrome.tabs.executeScript(tab.id, {file: 'view/js/SelectSaver.js'}, function(results){
      if (results){
      		message = {"type": "SelectedWebPage","URL":info.pageUrl,"title":tab.title,"data":results};
        	connect();
			sendNativeMessage(message);
      }
    });
}

function SaveAsHtml(info, tab){
    chrome.tabs.executeScript(tab.id, {file: 'view/js/FileSaver.js'}, function(results){
      if (results){
      		message = {"type": "WebPage","URL":info.pageUrl,"title":tab.title,"data":results};
      		connect();
			sendNativeMessage(message);       	
      }
    });
}





//右键菜单控制函数
chrome.contextMenus.onClicked.addListener(function(info, tab){
  if(info.menuItemId == 'SaveSelectedTxt'){
    SaveSelectedTxt(info, tab);
  }
  else if(info.menuItemId == 'SaveWebText'){
  	SaveWebText(info, tab);
  }
  else if(info.menuItemId == 'SaveWebImg'){
  	SaveSelectedImg(info, tab);
  }
  else if(info.menuItemId == 'SaveSelectedWebPage'){
  	SaveSelectedWebPage(info, tab);
  }
  else if(info.menuItemId == 'SaveWebPage'){
  	SaveAsHtml(info, tab);
  }
});
