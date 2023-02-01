<script lang="ts">
	import FlashOffFilled from "carbon-icons-svelte/lib/FlashOffFilled.svelte";
	import FlashFilled from "carbon-icons-svelte/lib/FlashFilled.svelte";
	import { Button } from "carbon-components-svelte";
	import { baseURL } from "$lib/store";
	let connected = false;
	const refresh = () => {
		fetch(`${baseURL}/ping`, {
			method: "GET",
		})
			.then((res) => res.json())
			.then((b) => {
				if (b["message"] == "pong") connected = true;
			});
	};
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
