<script lang="ts">
	import FlashOffFilled from "carbon-icons-svelte/lib/FlashOffFilled.svelte";
	import FlashFilled from "carbon-icons-svelte/lib/FlashFilled.svelte";
	import { Button } from "carbon-components-svelte";
	import { baseURL } from "$lib/store";
	let connected = false;
	let lidarConnected = false;
	const refresh = () => {
		fetch(`${baseURL}/ping`, {
			method: "GET",
		})
			.then((res) => res.json())
			.then((b) => {
				if (b["message"] == "pong") connected = true;
			});
	};
	const lidarRefresh = () => {
		fetch(`${baseURL}/lidar`, {
			method: "GET",
		})
			.then((res) => res.json())
			.then((b) => {
				if (b["message"] == "ping") {
					lidarConnected = true;
				} else {
					lidarConnected = false;
				}
			});
	};
	lidarRefresh();
	refresh();
</script>

<div class="checker">
	<span>Connection to ESP32:</span>
	<Button on:click={refresh}>Refresh</Button>
	{#if connected}
		<span style="color: green;">Connected <FlashFilled size={16} /></span>
	{:else}
		<span style="color: red;"
			>Not Connected <FlashOffFilled size={16} /></span
		>
	{/if}
</div>
<div class="checker">
	<span>Connection to LIDAR:</span>
	<Button on:click={lidarRefresh}>Refresh</Button>
	{#if lidarConnected}
		<span style="color: green;">Connected <FlashFilled size={16} /></span>
	{:else}
		<span style="color: red;"
			>Not Connected <FlashOffFilled size={16} /></span
		>
	{/if}
</div>

<style scoped>
	.checker {
		padding: 0.5rem;
		display: flex;
		font-size: 1rem;
		justify-content: center;
		align-items: center;
		gap: 0.5rem;
	}
</style>
