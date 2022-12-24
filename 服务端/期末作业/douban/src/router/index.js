import Vue from 'vue'
import VueRouter from 'vue-router'
Vue.use(VueRouter)
import Home from '../pages/Home/Home'
import Movies from "../pages/Movies/Movies"
import Ratings from '../pages/Ratings/Ratings'
import Us from "../pages/Us/Us"
import Words from '../pages/Words/Words'
export default new VueRouter({
    routes: [
        {
            path: "/",
            redirect:"/home"
    },
        {
        path: '/home',
        component:Home
        },
        {
            path: '/movies',
            component: Movies 
        },
        {
            path: '/rating',
            component:Ratings
        },
        {
            path: '/word',
            component:Words
        },
        {
            path: '/us',
            component:Us
        }
    ]
})