import Vue from 'vue'
import App from './App.vue'

Vue.config.productionTip = false

import router from '../router/index.js'

import {Collapse,CollapseItem,Button,Card,Row,Col,Icon,Submenu,MenuItem,MenuItemGroup,Upload,Rate,Loading} from 'element-ui' 
import 'element-ui/lib/theme-chalk/index.css'
import store from '../store/index.js'

import axios from 'axios'
Vue.use(axios);

Vue.use(Button);
Vue.use(Row);
Vue.use(Col);

var vm=new Vue({
	store:store,
	router:router,
	beforeCreate() {
		Vue.prototype.$bus=this;
	},
	methods:{
		
	},
	mounted() {
		
	},
    render: h => h(App),
});
vm.$mount('#app');
