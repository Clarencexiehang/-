<template>
	<div id="manage_div">
		<MainHead></MainHead>
		<router-link to="/main"></router-link>
		<router-link to="/personpage"></router-link>
		<router-link :to="{name:'quest'}"></router-link>
		<router-link :to="{name:'privatesend'}"></router-link>
		<router-view></router-view>
		<MainFooter></MainFooter>
	</div>
</template>

<script>
	import Main from './main_page/Main.vue'
	import MainHead from './main_page/MainHead.vue'
	import MainFooter from './main_page/MainFooter.vue'
	
	export default{
		name:'Manager.vue',
		components:{
			Main,
			MainHead,
			MainFooter
		}
	}
</script>

<style scoped>
	#manage_div{
		width: 100%;
		height: 100%;
		background-image: url('../assets/backimg/manager_bac.jpg');
		background-repeat: no-repeat;
	}
</style>