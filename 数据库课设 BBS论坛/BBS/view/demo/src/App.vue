<template>
  <div id="app">
	<router-link to="/log"></router-link>
	<router-link to="/register"></router-link>
	<router-link to="/manager"></router-link>
	<router-link to="/behind"></router-link>
	<router-view></router-view>
  </div>
</template>

<script>
	import Login from './components/log_page/Login.vue'
	import Manager from './components/Manager.vue'
	
	/* import Main from './components/Main.vue'
	import MainHead from './components/MainHead.vue'
	import MainFooter from './components/MainFooter.vue' */
	export default {
	  name: 'App',
	  components: {
		  Login,
		  Manager
	  }
	}
</script>

<style scoped>
	#app {
		position: relative;
		font-family: Avenir, Helvetica, Arial, sans-serif;
		-webkit-font-smoothing: antialiased;
		-moz-osx-font-smoothing: grayscale;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
		text-align: center;
		color: #2c3e50;
		background-repeat: repeat;
	}

</style>
