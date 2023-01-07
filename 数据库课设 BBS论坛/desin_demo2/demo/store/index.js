import Vue from 'vue'
import Vuex from 'vuex'
Vue.use(Vuex);

//actions 用于响应组件里的动作
var Actions={
	setUserName:function(context,data){
		console.log('actions setUserName ------------ ');
		context.commit('SETUSERNAME',data);
	}
};
//mutations 用于操作状态(数据)
var Mutations={
	SETUSERNAME:function(state,data){
		console.log('mutatipns SETUSERNAME ------------ ');
		state.nickname=data;
	}
};
//state 用于存储状态(数据)
var State={
	nickname:''
};
//创建 store 实例
var store = new Vuex.Store({
				actions:Actions,
				mutations:Mutations,
				state:State
				});
// 暴露(导出)store 
export default store;