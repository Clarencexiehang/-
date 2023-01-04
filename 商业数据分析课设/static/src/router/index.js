import Vue from 'vue'
import VueRouter from 'vue-router'
Vue.use(VueRouter)
import Home from '../pages/Home/Home'
import Stock from '../pages/Stock/Stock'
import Webits from '../pages/Webits/Webits'
import Us from "../pages/Us/Us"
export default new VueRouter({
	routes: [{
			path: "/",
			redirect: "/home"
		},
		{
			path: '/home',
			component: Home
		},
		{
			path: '/webits',
			component: Webits
		},
		{
			path: '/rating',
			component: Stock
		},
		{
			path: '/us',
			component: Us
		}
	]
})
