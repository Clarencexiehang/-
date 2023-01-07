import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

/* *************  登录页面 ***************** */
import Login from '../src/components/log_page/Login.vue'
import Regiter from '../src/components/log_page/Regiter.vue'

/* *************  manager 页面 ***************** */
import Manager from '../src/components/Manager.vue'


/* *************  main 页面 ***************** */
import Main from '../src/components/main_page/Main.vue'
import MainFirstPage from '../src/components/main_page/MainFirstPage.vue'
import ArticleDetail from '../src/components/main_page/ArticleDetail.vue'


/* *************  header 页面 ***************** */
import HotSearchBord from '../src/components/header/HotSearchBord.vue'
import PrivateSend from '../src/components/header/PrivateSend.vue'
import Care from '../src/components/header/Care.vue'
import MsgList from '../src/components/header/MsgList.vue'
import MsgDetail from '../src/components/header/MsgDetail.vue'



// 通知页面
import Notices from '../src/components/header/Notices.vue'






/* *************  footer 页面 ***************** */
import Ask from '../src/components/footer/Ask.vue'
import Suggest from '../src/components/footer/Suggest.vue'

/* *************  person 页面 ***************** */
import PersonPage from '../src/components/person_page/PersonPage.vue'
import ModifyInfo from '../src/components/person_page/ModifyInfo.vue'
import ArticleInfo from '../src/components/person_page/ArticleInfo.vue'
import Article from '../src/components/person_page/Article.vue'
import CareAbout from '../src/components/person_page/CareAbout.vue'
import Fans from '../src/components/person_page/Fans.vue'
import MyCollections from '../src/components/person_page/MyCollections.vue'
import History from '../src/components/person_page/History.vue'
import EditUserArt from '../src/components/person_page/EditUserArt.vue'



/**************************  后台管理 **************************/
import BehindManager from '../src/components/behind/BehindManager.vue'
import bHeader from '../src/components/behind/bHeader.vue'




// 用户账号管理
import UserAccountMag from '../src/components/behind/userAccMag/UserAccountMag.vue'
import DetailInfo from '../src/components/behind/userAccMag/DetailInfo.vue'

// 帖子管理
import ArticleMag from '../src/components/behind/articleMagr/ArticleMag.vue'
import hasNotices from '../src/components/behind/articleMagr/hasNotices.vue'
import UserArt from '../src/components/behind/articleMagr/UserArt.vue'
import ReEditAnnoc from '../src/components/behind/articleMagr/ReEditAnnoc.vue'
import UserArtDetail from '../src/components/behind/articleMagr/UserArtDetail.vue'


// 运营数据
import RunData from '../src/components/behind/rundata/RunData.vue'
import RunDataDetail from '../src/components/behind/rundata/RunDataDetail.vue'
import UserRegiterNum from '../src/components/behind/rundata/UserRegiterNum.vue'
import HotUser from '../src/components/behind/rundata/HotUser.vue'

// 发布公告
import PostNotice from '../src/components/behind/notices/PostNotice.vue'


var router=new VueRouter({
	mode:'history',
	routes:[
		{
			path:'/log',
			component:Login
		},
		{
		   	path:'/register',
			component:Regiter
		},
		{
			path:'/behind',
			name:'behind',
			component:BehindManager,
			children:[
				{
					path:'useraccountmag',
					name:'useraccountmag',
					component:UserAccountMag,
					children:[
						{
							path:'detailinfo',
							name:'detailinfo',
							component:DetailInfo
						}
					]
				},
				{
					path:'articlemag',
					name:'articlemag',
					component:ArticleMag,
					children:[
						{
							path:'hasnotices',
							name:'hasnotices',
							component:hasNotices
						},
						{
							path:'reeditannoc',
							name:'reeditannoc',
							component:ReEditAnnoc
						},
						{
							path:'userart',
							name:'userart',
							component:UserArt,
							children:[
								{
									path:'userartdetail',
									name:'userartdetail',
									component:UserArtDetail
								}
							]
						}
					]
				},
				{
					path:'rundata',
					name:'rundata',
					component:RunData,
					children:[
						{
							path:'rundatadetail',
							name:'rundatadetail',
							component:RunDataDetail,
							children:[
								{
									path:'userregiternum',
									name:'userregiternum',
									component:UserRegiterNum
								},
								{
									path:'hotuser',
									name:'hotuser',
									component:HotUser
								}
							]
						}
					]
				},
				{
					path:'postnotice',
					name:'postnotice',
					component:PostNotice
				}
			]
		},
		{
			path:'/manager',
			component:Manager,
			children:[
				{
					name:'main',
					path:'main',
					component:Main,
					children:[
						{
							path:'notices',
							name:'notices',
							component:Notices
						},
						{
							name:'privatesend',
							path:'privatesend',
							component:PrivateSend,
							children:[
								{
									path:'msglist',
									name:'msglist',
									component:MsgList
								},
								{
									path:'msgdetail',
									name:'msgdetail',
									component:MsgDetail
								}
							]
						},
						{
							name:'hotsearchbord',
							path:'hotsearchbord',
							component:HotSearchBord
						},
						{
							path:'care',
							name:'care',
							component:Care
						},
						{
							name:'mainfirstpage',
							path:'mainfirstpage',
							component:MainFirstPage,
						},
						{
							name:'articledetail',
							path:'articledetail/:cnickname/:article_id',
							component:ArticleDetail,
							props:true
						},
						{
							name:'ask',
							path:'ask',
							component:Ask
						},
						{
							name:'suggest',
							path:'suggest',
							component:Suggest
						},
						{
							path:'edituserart',
							name:'edituserart',
							component:EditUserArt
						}
					]
				},
				{
					name:'personpage',
					path:'personpage',
					component:PersonPage,
					children:[
						{
							name:'modify',
							path:'modify',
							component:ModifyInfo
						},
						{
							name:'articleinfo',
							path:'articleinfo',
							component:ArticleInfo,
							children:[
								{
									name:'article',
									path:'article',
									component:Article
								},
								{
									name:'careabout',
									path:'careabout',
									component:CareAbout
								},
								{
									name:'fans',
									path:'fans',
									component:Fans
								},
								{
									name:'mycollections',
									path:'mycollections',
									component:MyCollections
								},
								{
									name:'history',
									path:'history',
									component:History
								}
							]
						}
					]
				},
			]
		}
	]
})

// 全局前置路由守卫
router.beforeEach(function(to,from,next){
	console.log('------- from.path --------   ',from.path);
	console.log('------- to--------   ',to.path); 
	
	//(to.path=='/behind/useraccountmag'||to.path=='/behind/articlemag'||to.path=='/behind/articlemag/hasnotices'||to.path=='/behind/articlemag/reeditannoc'||to.path=='/behind/articlemag/userart'||to.path=='/behind/articlemag/userart/userartdetail'||to.path=='/behind/rundata'||to.path=='/behind/postnotice'||to.path=='/behind/rundata/rundatadetail'||to.path=='/behind/rundata/rundatadetail/userregiternum'||to.path=='/behind/rundata/rundatadetail/hotuser')
	
	// 对于后台管理员，可自由通过前置路由守卫
	var reg=new RegExp('^(/behind)');
	if(reg.test(to.path)){
		console.log('进入后台管理-------');
		next();
	}
	// 对于用户，需要校验用户信息
	else{
		if(from.path=='/'||from.path=='/log'){
			next();
		}
		else{
			var nickname=window.sessionStorage.getItem('nickname');
			if(nickname){
				// console.log('找到 用户 ',nickname);
				next();
			}else{
				console.log('请先登录 !!!!!!');
				location.href='http://localhost:8080/log';
			}
		}
	}
})

export default router





