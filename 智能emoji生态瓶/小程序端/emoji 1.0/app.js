//app.js
var hotapp = require('utils/hotapp.js');
App({
  onLaunch: function () {
    // Do something initial when launch.
  },
  onShow: function () {
    // Do something when show.
  },
  onHide: function () {
    // Do something when hide.
  },
  onError: function (msg) {
    console.log(msg)
  },
  globalData: 'I am global data'
})
const defaultTime = {
  defaultWorkTime: 25,
  defaultRestTime: 5
}



App({
  onLaunch() {
    console.log('App.onLaunch()');
  },
  onShow: function () {
  },
  onHide: function () {
  },

  //本应用全局数据
  globalData: {
    temperature: {},
    light: {},
    humidity: {},
    water: {},
    gas: {}
  }
})






/*
App({

  onLaunch: function()
   {
    let workTime = wx.getStorageSync('workTime')
    let restTime = wx.getStorageSync('restTime')
    if (!workTime) {
      wx.setStorage({
        key: 'workTime',
        data: defaultTime.defaultWorkTime
      })
    }
    if (!restTime) {
      wx.setStorage({
        key: 'restTime',
        data: defaultTime.defaultRestTime
      })
    }
  }
})
*/