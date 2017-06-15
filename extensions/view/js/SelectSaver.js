[].map.call(document.getElementsByTagName('html'), function(select){
  if (window.getSelection()) { //chrome,firefox,opera
        var range=window.getSelection().getRangeAt(0);
        var container = document.createElement('div');
        container.appendChild(range.cloneContents());
        return container.innerHTML;
        //return window.getSelection(); //只复制文本
    }
  //return select;
});